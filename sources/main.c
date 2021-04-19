/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/19 20:22:15 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "minishell.h"
#include "input.h"
#include "parser.h"
#include "environment.h"
#include <sys/ioctl.h>


void	print_pword(void *data)
{
	t_pword	*word;

	word = (t_pword  *)data;
	printf(">> type: %d, val: \"%s\"\n", word->type, word->value);
} 

int		process(t_minishell *shell)
{
	t_list		*words;
	char		*line;

	while (21)
	{
		minishell_write_title(shell);
		// TODO работаться уже с возвращаем значении
		if (input_get_next_line(shell->input, &line) == -1)
			return (0);
		printf(">\"%s\"\n", line);
		if (!parse_line(shell->env, line, &words))
			return (1); // TODO возврат ошибки
		// TODO вход для фабрики
		ft_list_foreach(words, print_pword);
		free(line);
		ft_list_free(&words, free);
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
