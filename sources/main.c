/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 14:40:28 by hgrampa          ###   ########.fr       */
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

		// TODO работаться уже с возвращаем значении
		if (!input_get_next_line(shell->input, &shell->line, shell))
			return (0); // TODO очистку при ошибках (вроде есть)
		if (shell->line == NULL)
			continue ;

		// TODO вырезать и переделать
		if (ft_strnstr(shell->line, "exit", ft_strlen(shell->line)))
		{
			free(shell->line);
			ft_list_free(&shell->words, pword_destroy);	
			minishell_exit(shell, 0);	
		}

		// printf(">\"%s\"\n", line);

		// Добавляю instance в историю
		if (!history_add(shell->history, shell->line))
		{
			free (shell->line);
			return (0); // TODO возврат ошибки
		}

		// Получаю слова от парсера
		if (!parse_line(shell->env, shell->line, &shell->words))
			return (1); // TODO возврат ошибки
		// отдаю слова фабрике
		if (!factory_run_line(shell->factory, shell->words, shell))
		{
			ft_list_free(&shell->words, pword_destroy);
			return (0);
		}

		// ft_list_foreach(words, pword_print);

		// if (gnl == 0)
		// 	minishell_exit(shell, 0);
	}
	return (1);
}

int		main(int argc, char const *argv[], char const *envp[])
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
	minishell_destroy(shell);
	return (result);
}
