/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_command_set.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 23:24:40 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 15:39:12 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"

int	factory_command_set_pipe(t_list **words, struct s_build_context *context)
{
	if ((*words)->next == NULL)
		return (err_print(_ERR_MULTL, 0, 258));
	*words = (*words)->next;
	context->command->is_pipe = 1;
	return (1);
}

int	factory_command_set_semicolon(t_list **words,
	struct s_build_context *context)
{
	*words = (*words)->next;
	context->command->is_pipe = 0;
	return (1);
}

int	factory_command_set_input(t_list **words, struct s_build_context *context)
{
	int		fd;
	t_pword	*word;

	if ((*words)->next == NULL)
		return (err_print_untoken("newline", 0));
	*words = (*words)->next;
	word = (t_pword *)(*words)->data;
	if (word->type != EWT_WORD)
		return (err_print_untoken(word->value, 0));
	if (context->command->input != -1)
		close(context->command->input);
	fd = open(word->value, O_RDONLY, S_IRWXU);
	if (fd == -1)
		return (err_print_nofile(word->value, 0));
	context->command->input = fd;
	return (1);
}

int	factory_command_set_output(t_list **words, struct s_build_context *context,
	int to_end)
{
	int		fd;
	t_pword	*word;

	if ((*words)->next == NULL)
		return (err_print_untoken("newline", 0));
	*words = (*words)->next;
	word = (t_pword *)(*words)->data;
	if (word->type != EWT_WORD)
		return (err_print_untoken(word->value, 0));
	if (context->command->output != -1)
		close(context->command->output);
	if (to_end)
		fd = open(word->value, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU);
	else
		fd = open(word->value, O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	if (fd == -1)
		return (err_print_nofile(word->value, 0));
	context->command->output = fd;
	return (1);
}

int	factory_command_set_argv(t_pword *word, struct s_build_context *context)
{
	if (!ft_list_add(&context->argl, word->value))
		return (0);
	return (1);
}
