/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:18:43 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 14:52:08 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"
#include "minishell.h"

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
	// TODO Узнать у дена зачем он это отдельным циклом делал (он не знает)
	if (com_pair.command->is_pipe || (com_pair.previous != NULL && com_pair.previous->is_pipe))
	{
		if (pipe(com_pair.command->pipe) == -1)
			return (-1); // TODO описание ошибки
	}
	pid = fork();
	if (pid == -1)
		return (-1); // TODO возврат ошибки
	else if (pid == 0)
	{
		if (!factory_exec_set_out(com_pair))
			exit(1); // TODO описание ошибки и очистка
		if (!factory_exec_set_in(com_pair))
			exit(1); // TODO описание ошибки и очистка
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

// TODO и закрытие in out
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

	waitpid(pid, &status, 0);
	// factory_exec_close_pipes(node);
	exit_code_clamp_set(status);
	return (1);
}

int	factory_exec_commands(t_factory *factory, t_minishell *shell)
{
	int			pid;
	t_dlist		*node;
	t_command	*command;

	node = factory->commands;
	while (node != NULL)
	{
		// command = (t_command *)node->data;
		// if ()
		pid = factory_exec_command(node, shell);
		if (pid > 0)
			factory_exec_close_pipes(node);
		else if (pid == -1)
		{
			factory->result = 0;
			return (0); // TODO А если уже есть открытые дети???
		}
		node = node->next;
	}
	factory_handle_parent(node, pid);
	return (1);
}
