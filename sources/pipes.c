#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"

#define SIDE_OUT    0
#define SIDE_IN     1

#define STDIN           0
#define STDOUT          1
#define STDERR          2

#define TYPE_END        0
#define TYPE_PIPE       1
#define TYPE_BREAK      2

typedef struct s_pipelist
{
	char				**args;
	int					len;
	int					type;
	int					pipes[2];
	struct s_pipelist	*previous;
	struct s_pipelist	*next;
}						t_pipelist;

int	list_to_beginning(t_pipelist **list)
{
	while (*list && (*list)->previous)
		*list = (*list)->previous;
	return (1);
}

int	list_clear(t_pipelist **cmds)
{
	t_pipelist	*tmp;
	int			i;

	list_to_beginning(cmds);
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

int	exit_fatal(void)
{
	printf("error: fatal\n");
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int	add_arg(t_pipelist *cmd, char *arg)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)ft_calloc(1, sizeof(*tmp) * (cmd->len + 2));
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
	cmd->args[i++] = ft_strdup(arg);
	cmd->args[i] = 0;
	cmd->len++;
	return (EXIT_SUCCESS);
}

int	list_push(t_pipelist **list, char *arg)
{
	t_pipelist	*new;

	new = (t_pipelist *)ft_calloc(1, sizeof(*new));
	if (new == NULL)
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

int	parse_arg(t_pipelist **cmds, char *arg)
{
	int	is_break;

	is_break = (ft_strncmp(";", arg, 2) == 0);
	if (is_break && !*cmds)
		return (EXIT_SUCCESS);
	else if (!is_break && (!*cmds || (*cmds)->type > TYPE_END))
		return (list_push(cmds, arg));
	else if (ft_strncmp("|", arg, 2) == 0)
		(*cmds)->type = TYPE_PIPE;
	else if (is_break)
		(*cmds)->type = TYPE_BREAK;
	else
		return (add_arg(*cmds, arg));
	return (EXIT_SUCCESS);
}

int	exec_cmd(t_pipelist *cmd, char **env)
{
	pid_t	pid;
	int		ret;
	int		status;

	ret = EXIT_FAILURE;
	if (cmd->type == TYPE_PIPE || (cmd->previous
			&& cmd->previous->type == TYPE_PIPE))
		if (pipe(cmd->pipes))
			return (exit_fatal());
	pid = fork();
	if (pid < 0)
		return (exit_fatal());
	else if (pid == 0)
	{
		if (cmd->type == TYPE_PIPE && dup2(cmd->pipes[SIDE_IN], STDOUT) < 0)
			return (exit_fatal());
		if (cmd->previous && cmd->previous->type == TYPE_PIPE
			&& dup2(cmd->previous->pipes[SIDE_OUT], STDIN) < 0)
			return (exit_fatal());
		ret = execve(cmd->args[0], cmd->args, env);
		if (ret < 0)
			printf("error: cannot execute %s\n", cmd->args[0]);
		exit(ret);
	}
	return (pid);
}

int	handle_parent(int ret, t_pipelist *cmd)
{
	int	status;

	waitpid(ret, &status, 0);
	if (cmd->type == TYPE_PIPE
		|| (cmd->previous && cmd->previous->type == TYPE_PIPE))
	{
		close(cmd->pipes[SIDE_IN]);
		if (!cmd->next || cmd->type == TYPE_BREAK)
			close(cmd->pipes[SIDE_OUT]);
	}
	if (cmd->previous && cmd->previous->type == TYPE_PIPE)
		close(cmd->previous->pipes[SIDE_OUT]);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}

int	exec_cmds(t_pipelist **cmds, char **env)
{
	t_pipelist	*crt;
	int			pid;

	list_to_beginning(cmds);
	while (*cmds)
	{
		crt = *cmds;
		pid = exec_cmd(crt, env);
		if (pid > 0)
		{
			if (crt->type == TYPE_PIPE || (crt->previous
					&& crt->previous->type == TYPE_PIPE))
			{
				close(crt->pipes[SIDE_IN]);
				if (!crt->next || crt->type == TYPE_BREAK)
					close(crt->pipes[SIDE_OUT]);
			}	
		}
		if (!(*cmds)->next)
			break ;
		*cmds = (*cmds)->next;
	}
	if (pid != 0)
		pid = handle_parent(pid, crt);
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	t_pipelist	*cmds;
	int			i;
	int			ret;

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
