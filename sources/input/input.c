/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:46:56 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 11:19:28 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_input	*input_create(void)
{
	t_input *input;

	input = (t_input *)ft_calloc(1, sizeof(t_input));
	if (input == NULL)
		return (NULL); // TODO код ошибки
	input->buffer = sbuffer_create(_INP_STR_BUFFSIZE);
	if (input->buffer == NULL)
	{
		free(input);
		return (NULL); // TODO код ошибки
	}
	input->term = term_create();
	if (input->term == NULL)
	{
		sbuffer_destroy(input->buffer);
		free(input);
		return (NULL); // TODO код ошибки
	}
	return (input);
}

int		input_destroy(t_input *input)
{
	sbuffer_destroy(input->buffer);
	term_destroy(input->term);
	if (input->save_line != NULL)
		free(input->save_line);
	free(input);
	return (1);
}

int		input_init(t_input *input)
{
	if (!term_init(input->term))
		return (0);
	return (1);
}
