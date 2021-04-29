/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:46:56 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 14:07:38 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_input	*input_create(void)
{
	t_input	*input;

	input = (t_input *)ft_calloc(1, sizeof(t_input));
	if (input == NULL)
		return (NULL);
	input->buffer = sbuffer_create(_INP_STR_BUFFSIZE);
	if (input->buffer == NULL)
	{
		free(input);
		return (NULL);
	}
	input->term = term_create();
	if (input->term == NULL)
	{
		sbuffer_destroy(input->buffer);
		free(input);
		return (NULL);
	}
	return (input);
}

int	input_destroy(t_input *input)
{
	sbuffer_destroy(input->buffer);
	term_destroy(input->term);
	if (input->save_line != NULL)
		free(input->save_line);
	free(input);
	return (1);
}

int	input_init(void)
{
	if (!term_init())
		return (0);
	return (1);
}
