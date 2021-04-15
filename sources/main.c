/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/15 21:19:54 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "minishell.h"
#include "input.h"
#include "parser.h"

void	print_word(void *data)
{
	printf(">>\"%s\"\n", (char *)data);
} 

int main(int argc, char const *argv[], char const *envp[])
{
	// t_env env;
	// ? env = env_create(envp);
	char	*line;
	t_input	*input;
	t_list	*words;

	input = input_create();
	words = NULL;
	write(0, SHELL_TITLE, SHELL_TITLE_LEN);
	t_list *history;
	
	// read(0, buff, 999);
	while (input_get_next_line(input, &line) > 0)
	{
		printf(">\"%s\"\n", line);
		ft_list_add(&history, line);


		if (!parse_line(line, &words))
			return (1); // обработка ошибки
		
		ft_list_foreach(words, print_word);
		free(line);
		ft_list_free(&words, free);
		write(0, SHELL_TITLE, SHELL_TITLE_LEN);
	}
	input_destroy(input);

	return (0);
}
