#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define SIDE_OUT    0
#define SIDE_IN     1

#define STDIN           0
#define STDOUT          1
#define STDERR          2

#define TYPE_END        0
#define TYPE_PIPE       1
#define TYPE_BREAK      2

typedef struct s_list
{
    char       **args;
    int         len;
    int         type;
    int         pipes[2];
    struct s_list   *previous;
    struct s_list   *next;
}               t_list;

int list_rewind(t_list **list)
{
    while (*list && (*list)->previous)
        *list = (*list)->previous;
    return (1);
}

int list_clear(t_list **cmds)
{
    t_list    *tmp;
    int        i;
    
    list_rewind(cmds);
    while (*cmds)
    {
        tmp = (*cmds)->next;
        i = 0;
        while (i < (*cmds)->len)
            free((*cmds)->args[i++]);
        free((*cmds)->args);
        free(*cmds);
        *cmds = tmp;
    }
    *cmds = NULL;
    return (EXIT_SUCCESS);
}

int exit_fatal(void)
{
	printf("error: fatal\n");
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int add_arg(t_list *cmd, char *arg)
{
	char **tmp;
	int i;
	
	i = 0;
	tmp = (char **)malloc(sizeof(*tmp) * (cmd->len + 2));
	if (tmp == NULL)
		return (exit_fatal());
	while (i < cmd->len)
	{
		tmp[i] = cmd->args[i];
		i++;
	}
	if (cmd->len > 0)
		free(cmd->args);
	cmd->args = tmp;
	cmd->args[i++] = strdup(arg);
	cmd->args[i] = 0;
	cmd->len++;
	return(EXIT_SUCCESS);
}

int list_push(t_list **list, char *arg)
{
    t_list    *new;
    
    if (!(new = (t_list*)malloc(sizeof(*new))))
        return (exit_fatal());
    new->args = NULL;
    new->len = 0;
    new->type = TYPE_END;
    new->previous = NULL;
    new->next = NULL;
    if (*list)
    {
        (*list)->next = new;
        new->previous = *list;
    }
    *list = new;
    return (add_arg(new, arg));
}

int parse_arg(t_list **cmds, char *arg)
{
   int    is_break;
    
    is_break = (strcmp(";", arg) == 0);
    if (is_break && !*cmds)
        return (EXIT_SUCCESS);
    else if (!is_break && (!*cmds || (*cmds)->type > TYPE_END))
        return (list_push(cmds, arg));
    else if (strcmp("|", arg) == 0)
        (*cmds)->type = TYPE_PIPE;
    else if (is_break)
        (*cmds)->type = TYPE_BREAK;
    else
        return (add_arg(*cmds, arg));
    return (EXIT_SUCCESS);
}

int exec_cmd(t_list *cmd, char **env)
{
	pid_t pid;
	int ret;
	int status;
	int pipe_open;
	
	ret = EXIT_FAILURE;
	pipe_open = 0;
	if (cmd->type == TYPE_PIPE || (cmd->previous && cmd->previous->type == TYPE_PIPE))
	{
		pipe_open = 1;
		if (pipe(cmd->pipes))
			return (exit_fatal());
	}
	pid = fork();
	if (pid < 0)
		return (exit_fatal());
	else if (pid == 0)
	{
		if (cmd->type == TYPE_PIPE && dup2(cmd->pipes[SIDE_IN], STDOUT) < 0)
			return (exit_fatal());
		if (cmd->previous && cmd->previous->type == TYPE_PIPE && dup2(cmd->previous->pipes[SIDE_OUT], STDIN) < 0)
			return (exit_fatal());
		ret = execve(cmd->args[0], cmd->args, env);
		if (ret < 0)
		{
			printf("error: cannot execute ");
			printf("%s\n", cmd->args[0]);
		}
		exit(ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (pipe_open)
		{
			close(cmd->pipes[SIDE_IN]);
			if (!cmd->next || cmd->type == TYPE_BREAK)
				close(cmd->pipes[SIDE_OUT]);
		}
		if (cmd->previous && cmd->previous->type == TYPE_PIPE)
			close(cmd->previous->pipes[SIDE_OUT]);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	return (ret);
}
				
int exec_cmds(t_list **cmds, char **env)
{
	t_list *crt;
	int ret;
	
	ret = EXIT_SUCCESS;
	list_rewind(cmds);
	while(*cmds)
	{
		crt = *cmds;
		ret = exec_cmd(crt, env);
		if (!(*cmds)->next)
			break ;
		*cmds = (*cmds)->next;
	}
	return (ret);
}
				
int main(int ac, char **av, char **env)
{
    t_list *cmds;
    int i;
    int ret;
    
    ret = EXIT_SUCCESS;
    cmds = NULL;
    i = 1;
    while (i < ac)
        parse_arg(&cmds, av[i++]);
   	if (cmds)
        ret = exec_cmds(&cmds, env);
    list_clear(&cmds);
    return (ret);
}
