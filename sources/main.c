/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 14:42:27 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "minishell.h"
#include "input.h"
#include "parser.h"
#include "environment.h"

void	print_pword(void *data)
{
	t_pword	*word;

	word = (t_pword  *)data;
	printf(">> type: %d, val: \"%s\"\n", word->type, word->value);
} 

int main(int argc, char const *argv[], char const *envp[])
{
	char	*line;
	t_input	*input;
	t_list	*words;
	t_env	*env;

	input = input_create();
	words = NULL;
	write(0, SHELL_TITLE, SHELL_TITLE_LEN);
	env = env_create(envp);
	if (env == NULL)
		return (0); // ! возврат ошибки

	// read(0, buff, 999);
	while (input_get_next_line(input, &line) > 0)
	{
		printf(">\"%s\"\n", line);


		if (!parse_line(env, line, &words))
			return (1); // ! возврат ошибки
	
		ft_list_foreach(words, print_pword);
		free(line);
		ft_list_free(&words, free);
		write(0, SHELL_TITLE, SHELL_TITLE_LEN);
	}
	input_destroy(input);

	return (0);
}
