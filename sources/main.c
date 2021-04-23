/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 11:30:20 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "input.h"
#include "parser.h"
#include "environment.h"
#include "pword.h"
#include "com_factory.h"

void	emul_exit(t_minishell *shell)
{
	minishell_on_exit(shell);
	minishell_destroy(shell);
	exit(0);
}

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

		if (ft_strnstr(line, "exit", ft_strlen(line)))
		{
			free(line);
			ft_list_free(&words, pword_destroy);	
			emul_exit(shell);	
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
		if (!com_factory_run_line(words, shell))
		{
			ft_list_free(&words, pword_destroy);
			return (0);
		}
		
		ft_list_foreach(words, pword_print);


		// Не чищу а отдаю истории чтоб не перевыделять
		line = NULL;
		ft_list_free(&words, pword_destroy);
		words = NULL;
		// 
		if (gnl == 0)
			emul_exit(shell);
	}
	return (1);
}

int		main(int argc, char const *argv[], char const *envp[])
{
	t_minishell	*shell;

	shell = minishell_create(_MINISHELL_TITLE, envp);
	if (shell == NULL)
		return (1); // TODO возврат ошибки
	if (!minishell_init(shell))
		return (1); // TODO возврат ошибки
	if (!process(shell))
		return (1);
	return (0);
}
