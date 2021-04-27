/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:18:43 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 18:57:56 by hgrampa          ###   ########.fr       */
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
		return (0); // TODO возврат ошибки
	else if (pid == 0)
	{
		shell->pid = pid;
		if (!factory_exec_set_out(com_pair))
			exit(1); // TODO описание ошибки и очистка
		if (!factory_exec_set_in(com_pair))
			exit(1); // TODO описание ошибки и очистка
		if (com_pair.command->is_buildin)
			ret = com_pair.command->buildin(com_pair.command->argv, shell);
		else
			ret = execve(com_pair.command->name, com_pair.command->argv, shell->env->represent);
		exit(ret);
	}
	com_pair.command->pid = pid;
	return (1);
}

int	factory_exec_buildin(t_dlist *node, t_minishell *shell)
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
		return (0); // TODO возврат ошибки
	else if (pid == 0)
	{
		shell->pid = pid;
		if (!factory_exec_set_out(com_pair))
			exit(1); // TODO описание ошибки и очистка
		if (!factory_exec_set_in(com_pair))
			exit(1); // TODO описание ошибки и очистка
		if (com_pair.command->is_buildin)
			ret = com_pair.command->buildin(com_pair.command->argv, shell);
		else
			ret = execve(com_pair.command->name, com_pair.command->argv, shell->env->represent);
		exit(ret);
	}
	com_pair.command->pid = pid;
	return (1);
}

// TODO и закрытие in out
int	factory_exec_close_pipes(t_dlist *node)
{
	struct s_comm_pair	com_pair;

	com_pair = get_com_pair(node);
	if (com_pair.command->input != -1)
		close(com_pair.command->input);
	if (com_pair.command->output != -1)
		close(com_pair.command->output);
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

int	factory_wait_command(t_dlist *node)
{
	int			status;
	t_command	*command;

	command = (t_command *)node->data;
	// if (!command->is_buildin && command->pid != -1)
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
	// сначала откроем всем пайпы
	// потом выполняем комманды в цикле уснанавливая pid
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
	// потом ждем все pid в другом цикле
	// потом закрываю все пайпы - дескрипторы
	node = factory->commands;
	while (node != NULL)
	{
		factory_wait_command(node);
		node = node->next;
	}
	return (1);
}
