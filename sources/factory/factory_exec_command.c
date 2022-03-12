/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_exec_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:07:46 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:34:28 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"
#include "minishell.h"

struct s_comm_pair	factory_get_com_pair(t_dlist *node)
{
	struct s_comm_pair	pair;

	pair.command = (t_command *)node->data;
	if (node->previous != NULL)
		pair.previous = (t_command *)node->previous->data;
	else
		pair.previous = NULL;
	return (pair);
}

int	factory_exec_set_out(struct s_comm_pair	pair)
{
	int	result;

	result = 1;
	if (pair.command->output != -1)
		result = dup2(pair.command->output, STDOUT_FILENO);
	else if (pair.command->is_pipe)
		result = dup2(pair.command->pipe[_PIPE_SIDE_IN], STDOUT_FILENO);
	if (result == -1)
		return (0);
	return (1);
}

int	factory_exec_set_in(struct s_comm_pair	pair)
{
	int	result;

	result = 1;
	if (pair.command->input != -1)
		result = dup2(pair.command->input, STDIN_FILENO);
	else if (pair.previous != NULL && pair.previous->is_pipe)
		result = dup2(pair.previous->pipe[_PIPE_SIDE_OUT], STDIN_FILENO);
	if (result == -1)
		return (0);
	return (1);
}

int	factory_exec_command(t_dlist *node, t_minishell *shell)
{
	struct s_comm_pair	pair;

	pair = factory_get_com_pair(node);
	if (pair.command->name == NULL)
		return (1);
	if (pair.command->is_buildin)
		return (factory_exec_buildin(pair, shell));
	else
		return (factory_exec_bin(pair, shell));
}
