/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:22:31 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 14:07:43 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "input.h"
#include "sbuffer.h"

int	input_set_line(t_input *input, char *line)
{
	term_clear_line();
	ft_putstr_fd(line, STDOUT_FILENO);
	sbuffer_clear(input->buffer);
	sbuffer_add_str(input->buffer, line);
	input->line_len = ft_strlen(line);
	return (1);
}

int	input_save_line(t_input *input)
{
	if (input->save_line == NULL)
	{
		input->save_line = ft_strdup(input->buffer->str);
		if (input->save_line == NULL)
			return (0);
	}
	return (1);
}

int	input_restore_save_line(t_input *input)
{
	char	*line;

	term_clear_line();
	line = input->save_line;
	ft_putstr_fd(line, STDOUT_FILENO);
	sbuffer_clear(input->buffer);
	sbuffer_add_str(input->buffer, line);
	input->line_len = ft_strlen(line);
	free(line);
	input->save_line = NULL;
	return (1);
}
