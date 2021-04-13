/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/13 18:59:11 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "minishell.h"
#include "input.h"

int main(int argc, char const *argv[], char const *envp[])
{
	// t_env env;
	// ? env = env_create(envp);
	char	*line;
	t_input	*input;

	input = input_create();

	write(0, SHELL_TITLE, SHELL_TITLE_LEN);
	// read(0, buff, 999);
	while (input_get_next_line(input, &line) > 0)
	{
		printf(">\"%s\"\n", line);
		free(line);
		write(0, SHELL_TITLE, SHELL_TITLE_LEN);
	}
	
	input_destroy(input);

	return (0);
}
