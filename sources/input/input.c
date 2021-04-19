/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:46:56 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/19 19:24:36 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_input *input_create(void)
{
	t_input *input;

	input = (t_input *)ft_calloc(1, sizeof(t_input));
	if (input == NULL)
		return (NULL); // TODO код ошибки
	input->buffer = sbuffer_create(INP_STR_BUFFSIZE);
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

int	input_destroy(t_input *input)
{
	sbuffer_destroy(input->buffer);
	term_destroy(input->term);
	free(input);
	return (1);
}

int input_read(t_input *input)
{
	int		read_len;
	char	read_buffer[INP_READ_BUFFSIZE + 1];

	ft_bzero(read_buffer, INP_READ_BUFFSIZE + 1);
	read_len = read(0, read_buffer, INP_READ_BUFFSIZE);
	if (read_len == -1)
		return (0); // TODO код ошибки
	if (term_take_input(read_buffer, read_len))
		return (1);
	else
	{
		write(STDOUT_FILENO, read_buffer, read_len);
		sbuffer_add_str(input->buffer, read_buffer);
	}
	return (1);
}

int	input_has_next_line(t_input *input, int *index)
{
	int		i;
	char	*buffer;
	
	buffer = input->buffer->str;
	i = -1;
	while (buffer[++i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			*index = i;
			return (1);
		}
		// TODO Суда EOF (или не суда так как если EOF то шел должен закрытся)
	}
	return (0);
}

// ! TODO история не добавляется к буферу
// TODO проверить cntl+v нескольких строк (не будет работать)
// TODO добавить EOF как конец команды (или всего процесса)
int	input_get_next_line(t_input *input, char **line)
{
	int	next_i;

	term_on_new_line();
	while (!input_has_next_line(input, &next_i))
	{
		if (!input_read(input))
			return (-1); // TODO код ошибки
	}
	*line = ft_strndup(input->buffer->str, next_i);
	sbuffer_clear(input->buffer);
	return (1);
}
