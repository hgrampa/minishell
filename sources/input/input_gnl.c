/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:19:09 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 13:25:40 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "errors.h"

static int	input_has_next_line(t_input *input, int *index)
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
	}
	return (0);
}

static int	input_read(t_input *input, t_minishell *shell)
{
	int				read_len;
	char			read_buffer[_INP_READ_BUFFSIZE + 1];
	enum e_key_type	key;

	ft_bzero(read_buffer, _INP_READ_BUFFSIZE + 1);
	read_len = read(0, read_buffer, _INP_READ_BUFFSIZE);
	if (read_len == -1)
		return (-1); // TODO код ошибки
	if (read_len == 0)
		return (0);
	key = term_key_type(read_buffer, read_len);
	if (key == EKT_NOTKEY)
	{
		input->line_len += read_len;
		write(STDOUT_FILENO, read_buffer, read_len);
		sbuffer_add_str(input->buffer, read_buffer);
	}
	else
	{
		if (input_take_key(key, shell))
			return (1); // TODO код ошибки
		else
			return (-1);
	}
	return (1);
}

// TODO история не добавляется к буферу
// TODO проверить cntl+v нескольких строк (не будет работать)
// TODO добавить EOF как конец команды (или всего процесса)
int			input_get_next_line(t_input *input, char **line, t_minishell *shell)
{
	int	next_i;
	int	read_res;

	input->line_len = 0;
	term_on_new_line();
	if(!term_set_mode(input->term))
		return (-1); // TODO код ошибки
	while (!input_has_next_line(input, &next_i))
	{
		read_res = input_read(input, shell);
		if (read_res == -1)
			return (-1); // TODO код ошибки
		else if (read_res == 0)
			break ;
	}
	*line = ft_strndup(input->buffer->str, next_i);
	sbuffer_clear(input->buffer);
	if(!term_reset_mode(input->term))
		return (-1); // TODO код ошибки
	return (1);
}
