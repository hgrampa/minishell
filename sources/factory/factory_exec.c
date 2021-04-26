/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:18:43 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/26 18:15:42 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"

struct s_comm_pair get_com_pair(t_dlist *node)
{
	struct s_comm_pair	com_pair;

	com_pair.command = (t_command *)node->data;
	if (node->previous != NULL)
		com_pair.previous = (t_command *)node->previous->data;
	else
		com_pair.previous = NULL;
	return (com_pair);
}

int factory_exec_set_out(struct s_comm_pair	com_pair)
{
	int	result;
	
	result = 1;
	
	if (com_pair.command->output != -1)
		result = dup2(com_pair.command->output, STDOUT_FILENO);
	else if (com_pair.command->is_pipe)
		result = dup2(com_pair.command->pipe[_PIPE_SIDE_IN], STDOUT_FILENO);
	if (result == -1)
		return (0); // TODO описание ошибки
	return (1);
}

int factory_exec_set_in(struct s_comm_pair	com_pair)
{
	int	result;
	
	result = 1;
	if (com_pair.command->input != -1)
		result = dup2(com_pair.command->input, STDIN_FILENO);
	else if (com_pair.previous != NULL && com_pair.previous->is_pipe)
		result = dup2(com_pair.previous->pipe[_PIPE_SIDE_OUT], STDIN_FILENO);
	if (result == -1)
		return (0); // TODO описание ошибки
	return (1);
}

int	factory_exec_command(t_dlist *node, t_minishell *shell)
{
	pid_t				pid;
	int					ret;
	struct s_comm_pair	com_pair;

	com_pair = get_com_pair(node);
	if (com_pair.command->is_pipe || (com_pair.previous != NULL && com_pair.previous->is_pipe))
	{
		if (pipe(com_pair.command->pipe) == -1)
			return (0); // TODO описание ошибки
	}
	pid = fork();
	if (pid == -1)
		return (0); // TODO возврат ошибки
	else if (pid == 0)
	{
		if (!factory_exec_set_out(com_pair))
			exit(1); // TODO описание ошибки и очистка
		if (!factory_exec_set_in(com_pair))
			exit(1); // TODO описание ошибки и очистка
		if (com_pair.command->is_buildin)
			com_pair.command->buildin(com_pair.command->argv, shell); // TODO возвращение кода возврата
		else
		{
			ret = execve(com_pair.command->name, com_pair.command->argv, shell->env->represent);
			if (ret < 0)
				return (0); // TODO описание ошибки или выход? и очистка
		}
		exit(ret); 
	}
	return (pid);
}

int	factory_exec_close_pipes(t_dlist *node)
{
	struct s_comm_pair	com_pair;

	com_pair = get_com_pair(node);
	if (com_pair.command->is_pipe || (com_pair.previous != NULL
		&& com_pair.previous->is_pipe))
	{
		close(com_pair.command->pipe[_PIPE_SIDE_IN]);
		if (node->next == NULL)
			close(com_pair.command->pipe[_PIPE_SIDE_OUT]);
	}
	if (com_pair.previous != NULL && com_pair.previous->is_pipe)
		close(com_pair.previous->pipe[_PIPE_SIDE_OUT]);
	return (1);
}

int	factory_handle_parent(t_dlist *node, int pid)
{
	int			status;
	t_command	*command;
	t_command	*previous;

	waitpid(pid, &status, 0);
	// factory_exec_close_pipes(node);
	if (WIFEXITED(status)) // ! TODO запрещены ||
		pid = WEXITSTATUS(status); // ! TODO запрещены
	return (pid);
}

int	factory_exec_commands(t_factory *factory, t_minishell *shell)
{
	int			pid;
	t_dlist		*node;
	t_command	*command;

	node = factory->commands;
	while (node != NULL)
	{
		pid = factory_exec_command(node, shell);
		if (pid > 0)
			factory_exec_close_pipes(node);
		node = node->next;
	}
	pid = factory_handle_parent(node, pid);
	// если надо верну пид в фабрике
	return (1);
}
