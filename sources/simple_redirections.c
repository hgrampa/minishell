#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft.h"

#define STDIN           		0
#define STDOUT          		1
#define STDERR          		2
#define TYPE_END        		0
#define TYPE_PIPE       		1
#define TYPE_BREAK      		2
#define REDIR_RIGHT        		3
#define REDIR_DOUBLE_RIGHT		4
#define REDIR_LEFT				5

int open_fd(int type, char *name)
{
	int fd;

	if (type == REDIR_RIGHT)
		fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	else if (type == REDIR_DOUBLE_RIGHT)
		fd = open(name, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	else if (type == REDIR_LEFT)
		fd = open(name, O_RDONLY, S_IRWXU);
	return(fd);
}

void exec_cmd(char **args, int type, int fd, char **env)
{
	pid_t pid;
	int ret;
	int status;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (type == REDIR_LEFT)
			ret = dup2(fd, STDIN);
		else
			ret = dup2(fd, STDOUT);
		if (ret < 0)
			printf("holy shit\n");
		ret = execve(args[0], args, env);
		if (ret == -1)
			printf("holy shit\n");
	}
	if (pid > 0)
	{
			waitpid(pid, &status, 0);
			close(fd);
	}

}


void exec_redirect(int type, char *name, char **args, char **env)
{
	// int type;
	int fd;

	// if (ft_strncmp(">", args[1], 2) == 0)
	// 	type = REDIR_RIGHT;
	// else if (ft_strncmp(">>", args[1], 3) == 0)
	// 	type = REDIR_DOUBLE_RIGHT;
	// else if (ft_strncmp("<", args[1], 2) == 0)
	// 	type = REDIR_LEFT;
	// else 
	// 	type = 0;
	fd = open_fd(type, name);
	if (fd == -1)
	{
		printf("error\n");
		return ;
	}
	exec_cmd(args, type, fd, env);	
}

int	main(int ac, char **av, char **env)
{
	char **args;

	args = (char **)ft_calloc(1, sizeof(char *) * 4);

	int type = REDIR_DOUBLE_RIGHT;
	//int type = REDIR_RIGHT;
	args[0] = ft_strdup("/bin/date");
	args[1] = 0;

	// int type = REDIR_LEFT;
	// args[0] = ft_strdup("/usr/bin/grep");
	// args[1] = ft_strdup("Sat");
	// args[3] = 0;


	char *name = ft_strdup("123.txt");
	exec_redirect(type, name, args, env);	
	return (0);
}