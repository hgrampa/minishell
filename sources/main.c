/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/26 17:02:22 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/signal.h>
#include "minishell.h"
#include "input.h"
#include "parser.h"
#include "environment.h"
#include "pword.h"
#include "factory.h"

void	signal_int_handler(int signum);
void	signal_quit_handler(int signum);

int		process(t_minishell *shell)
{
	t_list		*words;
	char		*line;
	int			gnl;

	words = NULL;
	line = NULL;
	while (21)
	{
		minishell_write_title(shell);
		// TODO работаться уже с возвращаем значении
		gnl = input_get_next_line(shell->input, &line, shell);
		if (gnl == -1)
			return (0); // TODO возврат ошибки
		if (line == NULL)
			continue ;
		if (ft_strnstr(line, "exit", ft_strlen(line)))
		{
			free(line);
			ft_list_free(&words, pword_destroy);	
			minishell_exit(shell, 0);	
		}

		printf(">\"%s\"\n", line);
		
		// Добавляю instance в историю
		if (!history_add(shell->history, line))
		{
			free (line);
			return (0); // TODO возврат ошибки
		}

		// Получаю слова от парсера
		if (!parse_line(shell->env, line, &words))
			return (1); // TODO возврат ошибки
		// отдаю слова фабрике
		if (!factory_run_line(words, shell))
		{
			ft_list_free(&words, pword_destroy);
			return (0);
		}
		
		// ft_list_foreach(words, pword_print);


		// Не чищу а отдаю истории чтоб не перевыделять
		line = NULL;
		ft_list_free(&words, pword_destroy);
		words = NULL;
		// 
		if (gnl == 0)
			minishell_exit(shell, 0);
	}
	return (1);
}

int		main(int argc, char const *argv[], char const *envp[])
{
	t_minishell	*shell;

	signal(SIGINT, signal_int_handler);
	signal(SIGQUIT, signal_quit_handler);
	shell = minishell_create(_MINISHELL_TITLE, envp);
	if (shell == NULL)
		return (1); // TODO возврат ошибки
	if (!minishell_init(shell))
		return (1); // TODO возврат ошибки
	if (!process(shell))
		return (1);
	return (0);
}
