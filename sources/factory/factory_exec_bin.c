/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_exec_bin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:05:38 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 13:53:31 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"
#include "minishell.h"

static void	factory_exec_bin_child(struct s_comm_pair pair, t_minishell *shell)
{
	int	ret;

	if (!factory_exec_set_out(pair))
		exit(1);
	if (!factory_exec_set_in(pair))
		exit(1);
	ret = execve(pair.command->name, pair.command->argv, shell->env->represent);
	exit(0);
}

int	factory_exec_bin(struct s_comm_pair	pair, t_minishell *shell)
{
	pid_t	pid;

	if (pair.command->is_pipe
		|| (pair.previous != NULL && pair.previous->is_pipe))
	{
		if (pipe(pair.command->pipe) == -1)
			return (err_print(NULL, 0, 1));
	}
	pid = fork();
	if (pid == -1)
		return (err_print(NULL, 0, 1));
	else if (pid == 0)
		factory_exec_bin_child(pair, shell);
	pair.command->pid = pid;
	return (1);
}
