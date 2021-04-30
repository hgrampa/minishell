/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:31:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/signal.h>
#include "minishell.h"
#include "input.h"
#include "parser.h"
#include "environment.h"
#include "pword.h"
#include "factory.h"

static int	process(t_minishell *shell)
{
	while (shell->process)
	{
		minishell_at_newline(shell);
		if (!input_get_next_line(shell->input, &shell->line, shell))
			return (0);
		if (shell->line == NULL)
			continue ;
		if (!history_add(shell->history, shell->line))
		{
			free (shell->line);
			return (0);
		}
		if (!parse_line(shell, shell->line, &shell->words))
			return (0);
	}
	return (1);
}

int	main(int argc, char const *argv[], char const *envp[])
{
	int			result;
	t_minishell	*shell;

	shell = minishell_create(_MINISHELL_TITLE, envp);
	if (shell == NULL)
		return (err_print(NULL, 1, 1));
	result = 0;
	if (minishell_init(shell))
	{
		if (!process(shell))
			result = 1;
	}
	else
		result = 1;
	minishell_exit(shell, result);
	argc = 0;
	argv = 0;
	return (0);
}
