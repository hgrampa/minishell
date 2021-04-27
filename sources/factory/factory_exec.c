/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:18:43 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 20:39:10 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"
#include "minishell.h"

struct s_comm_pair get_com_pair(t_dlist *node)
{
	struct s_comm_pair	pair;

	pair.command = (t_command *)node->data;
	if (node->previous != NULL)
		pair.previous = (t_command *)node->previous->data;
	else
		pair.previous = NULL;
	return (pair);
}

int factory_exec_set_out(struct s_comm_pair	pair)
{
	int	result;
	
	result = 1;
	
	if (pair.command->output != -1)
		result = dup2(pair.command->output, STDOUT_FILENO);
	else if (pair.command->is_pipe)
		result = dup2(pair.command->pipe[_PIPE_SIDE_IN], STDOUT_FILENO);
	if (result == -1)
		return (0); // TODO описание ошибки
	return (1);
}

int factory_exec_set_in(struct s_comm_pair	pair)
{
	int	result;

	result = 1;
	if (pair.command->input != -1)
		result = dup2(pair.command->input, STDIN_FILENO);
	else if (pair.previous != NULL && pair.previous->is_pipe)
		result = dup2(pair.previous->pipe[_PIPE_SIDE_OUT], STDIN_FILENO);
	if (result == -1)
		return (0); // TODO описание ошибки
	return (1);
}


int	factory_exec_bin(struct s_comm_pair	pair, t_minishell *shell)
{
	pid_t				pid;
	int					ret;

	// TODO Узнать у дена зачем он это отдельным циклом делал (он не знает)
	if (pair.command->is_pipe || (pair.previous != NULL && pair.previous->is_pipe))
	{
		if (pipe(pair.command->pipe) == -1)
			return (-1); // TODO описание ошибки
	}
	pid = fork();
	if (pid == -1)
		return (0); // TODO возврат ошибки
	else if (pid == 0)
	{
		shell->pid = pid;
		if (!factory_exec_set_out(pair))
			exit(1); // TODO описание ошибки и очистка
		if (!factory_exec_set_in(pair))
			exit(1); // TODO описание ошибки и очистка
		if (pair.command->is_buildin)
			ret = pair.command->buildin(pair.command->argv, shell);
		else
			ret = execve(pair.command->name, pair.command->argv, shell->env->represent);
		exit(ret);
	}
	pair.command->pid = pid;
	return (1);
}

int	factory_exec_buildin(struct s_comm_pair	pair, t_minishell *shell)
{
	pid_t				pid;
	int					ret;

	if (pair.command->is_pipe || (pair.previous != NULL && pair.previous->is_pipe))
	{
		if (pipe(pair.command->pipe) == -1)
			return (-1); // TODO описание ошибки
		pid = fork();
		if (pid == -1)
			return (0); // TODO возврат ошибки
		else if (pid == 0)
		{
			shell->pid = pid;
			if (!factory_exec_set_out(pair))
				exit(1); // TODO описание ошибки и очистка
			if (!factory_exec_set_in(pair))
				exit(1); // TODO описание ошибки и очистка
			ret = pair.command->buildin(pair.command->argv, shell);
			exit(ret);
		}
	}
	else
		exit_code_set(pair.command->buildin(pair.command->argv, shell));
	return (1);
}

int	factory_exec_command(t_dlist *node, t_minishell *shell)
{
	struct s_comm_pair	pair;

	pair = get_com_pair(node);
	if (pair.command->name == NULL)
		return (1);
	if (pair.command->is_buildin)
		return (factory_exec_buildin(pair, shell));
	else
		return (factory_exec_bin(pair, shell));
}

int	factory_exec_close_pipes(t_dlist *node)
{
	struct s_comm_pair	pair;

	pair = get_com_pair(node);
	if (pair.command->input != -1)
		close(pair.command->input);
	if (pair.command->output != -1)
		close(pair.command->output);
	if (pair.command->is_pipe || (pair.previous != NULL
		&& pair.previous->is_pipe))
	{
		close(pair.command->pipe[_PIPE_SIDE_IN]);
		if (node->next == NULL)
			close(pair.command->pipe[_PIPE_SIDE_OUT]);
	}
	if (pair.previous != NULL && pair.previous->is_pipe)
		close(pair.previous->pipe[_PIPE_SIDE_OUT]);
	return (1);
}

int	factory_wait_command(t_dlist *node)
{
	int			status;
	t_command	*command;

	command = (t_command *)node->data;
	if (command->pid != -1)
	{
		waitpid(command->pid, &status, 0);
		factory_exec_close_pipes(node);
		exit_code_clamp_set(status);
	}
	return (1);
}

int	factory_exec_commands(t_factory *factory, t_minishell *shell)
{
	t_dlist		*node;

	node = factory->commands;
	while (node != NULL)
	{
		if (!factory_exec_command(node, shell))
		{
			factory->result = 0;
			break ;
			// return (0); // TODO А если уже есть открытые дети???
		}
		node = node->next;
	}
	node = factory->commands;
	while (node != NULL)
	{
		factory_wait_command(node);
		node = node->next;
	}
	return (1);
}
