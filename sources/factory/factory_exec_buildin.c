/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_exec_buildin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:04:29 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/28 18:20:25 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"
#include "minishell.h"

static int	factory_restore_std(int std_save, int std_num, int fd)
{
	int	result;

	result = dup2(std_save, std_num);
	close(std_save);
	close(fd);
	return (result);
}

static int	factory_exec_buildin_no_pipe(struct s_comm_pair pair,
	t_minishell *shell)
{
	int	result;
	int	save_stdout;
	int	save_stdin;

	result = 1;
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (pair.command->input != -1)
		result = dup2(pair.command->input, STDIN_FILENO);
	if (pair.command->output != -1)
		result = dup2(pair.command->output, STDOUT_FILENO);
	exit_code_set(pair.command->buildin(pair.command->argv, shell));
	if (pair.command->input != -1)
		factory_restore_std(save_stdin, STDIN_FILENO, pair.command->input);
	if (pair.command->output != -1)
		factory_restore_std(save_stdout, STDOUT_FILENO, pair.command->output);
	return (result);
}

static void	factory_exec_buildin_child(struct s_comm_pair pair,
	t_minishell *shell)
{
	int	ret;

	if (!factory_exec_set_out(pair))
		exit(1);
	if (!factory_exec_set_in(pair))
		exit(1);
	ret = pair.command->buildin(pair.command->argv, shell);
	exit(ret);
}

int	factory_exec_buildin(struct s_comm_pair pair, t_minishell *shell)
{
	pid_t				pid;

	if (pair.command->is_pipe
		|| (pair.previous != NULL && pair.previous->is_pipe))
	{
		if (pipe(pair.command->pipe) == -1)
			return (err_print(NULL, 0, 1));
		pid = fork();
		if (pid == -1)
			return (err_print(NULL, 0, 1));
		else if (pid == 0)
			factory_exec_buildin_child(pair, shell);
		pair.command->pid = pid;
	}
	else
		return (factory_exec_buildin_no_pipe(pair, shell));
	return (1);
}
