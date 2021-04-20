/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/20 13:41:03 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "minishell.h"
#include "input.h"
#include "parser.h"
#include "environment.h"
#include <sys/ioctl.h>


void	pword_print(void *data)
{
	t_pword	*word;

	word = (t_pword  *)data;
	printf(">> type: %d, val: \"%s\"\n", word->type, word->value);
}

void	pword_destroy(void	*data)
{
	t_pword	*word;

	word = (t_pword  *)data;
	free(word->value);
	free(word);
}

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

	words = NULL;
	line = NULL;
	while (21)
	{
		minishell_write_title(shell);
		// TODO работаться уже с возвращаем значении
		if (input_get_next_line(shell->input, &line) == -1)
			return (0);
		
		if (ft_strnstr(line, "exit", ft_strlen(line)))
		{
			line = NULL;
			ft_list_free(&words, pword_destroy);	
			emul_exit(shell);	
		}

		printf(">\"%s\"\n", line);
		// Если strlen(line) == 0 то ниче не делаю
		// Добавляю instance в историю
		if (!history_add(shell->history, line))
		{
			free (line);
			return (0); // TODO возврат ошибки
		}
		if (!parse_line(shell->env, line, &words))
			return (1); // TODO возврат ошибки
		// TODO вход для фабрики
		ft_list_foreach(words, pword_print);
		// Не чищу а отдаю истории чтоб не перевыделять
		line = NULL;
		ft_list_free(&words, pword_destroy);
		// history_serealize(shell->history);
	}
	input_destroy(shell->input);
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
