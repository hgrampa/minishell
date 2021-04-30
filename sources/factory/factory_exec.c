/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:18:43 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 12:56:46 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"
#include "minishell.h"

int	factory_close_pipes(t_dlist *node)
{
	struct s_comm_pair	pair;

	pair = factory_get_com_pair(node);
	if (pair.command->input != -1)
		close(pair.command->input);
	if (pair.command->output != -1)
		close(pair.command->output);
	if (pair.command->is_pipe
		|| (pair.previous != NULL && pair.previous->is_pipe))
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
	int			exit_code;
	t_command	*command;

	command = (t_command *)node->data;
	if (command->pid != -1)
	{
		waitpid(command->pid, &status, 0);
		exit_code = exit_code_peek();
		if (!(exit_code == 130 || exit_code == 131))
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
			factory_close_pipes(node);
			factory->result = 0;
			break ;
		}
		factory_close_pipes(node);
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
