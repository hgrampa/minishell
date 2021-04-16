/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:46:56 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 16:00:27 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

t_input *input_create(void)
{
	t_input *input;

	input = (t_input *)ft_calloc(1, sizeof(t_input));
	if (input == NULL)
		return (NULL);
	return (input);
}

int	input_destroy(t_input *input)
{
	if (input->buffer != NULL)
		free(input->buffer);
	return (1);
}

int input_read(t_input *input)
{
	int		read_len;
	char	buffer[INP_READ_BUFFSIZE + 1];
	char	*new_buffer;

	ft_bzero(buffer, INP_READ_BUFFSIZE + 1);
	read_len = read(0, buffer, INP_READ_BUFFSIZE);
	if (read_len == -1)
		return (0);
	if (input->buffer == NULL)
		input->buffer = ft_strdup(buffer);
	else
	{
		new_buffer = ft_concat2(input->buffer, buffer);
		free(input->buffer);
		input->buffer = new_buffer;
	}
	return (1);
}

int	input_has_next_line(t_input *input, int *index)
{
	int i;
	char *buffer;
	
	buffer = input->buffer;
	if (buffer == NULL)
		return (0);
	i = -1;
	while (buffer[++i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			*index = i;
			return (1);
		}
	}
	return (0);
}

// TODO наверно луче убрать перенос строки из результата
// TODO читает только 1024 символа (вроде как это кап количества символов в буфере ввода)
// ! если произошел перенос из-за рамок окна не дает удалить строки выше backспейсом
// TODO добавить EOF как конец команды (или всего процесса)
int	input_get_next_line(t_input *input, char **line)
{
	int	next_i;
	
	while (!input_has_next_line(input, &next_i))
	{
		if (!input_read(input))
			return (-1);
	}
	*line = ft_strndup(input->buffer, next_i);
	free(input->buffer);
	input->buffer = NULL;
	return (1);
}

void input_reset_mode(t_input *input)
{
	tcsetattr(0, TCSANOW, &input->tsave);
}

void input_set_mode(t_input *input)
{
	// if (!isatty(0))
	// {
	// 	fprintf(stderr, "Not a terminal.\n");
	// 	exit(1);
	// }

	// tcgetattr(0, &input->tsave);
	// memcpy(&input->tattr, &input->tsave, sizeof(struct termios));
	
	/* включаем неканонический режим без эха */
	// tattr.c_lflag &= ~(ICANON|ECHO);
	/* считываем минимум по одному символу */
	// tattr.c_cc[VMIN] = 1;
	// tattr.c_cc[VTIME] = 0;

	// tcsetattr(0, TCSAFLUSH, &input->tattr);
}

