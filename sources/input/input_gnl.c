/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:19:09 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 14:08:15 by hgrampa          ###   ########.fr       */
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
	read_len = read(STDIN_FILENO, read_buffer, _INP_READ_BUFFSIZE);
	if (read_len == -1)
		return (err_print(NULL, 0, 1));
	key = term_key_type(read_buffer, read_len);
	if (key == EKT_NOTKEY)
	{
		input->line_len += read_len;
		write(STDOUT_FILENO, read_buffer, read_len);
		sbuffer_add_str(input->buffer, read_buffer);
	}
	else
		return (input_take_key(key, shell));
	return (1);
}

int	input_get_next_line(t_input *input, char **line, t_minishell *shell)
{
	int	next_i;

	input->line_len = 0;
	input->abort = 0;
	if (!term_on_new_line(input->term))
		return (0);
	while (!input->abort && !input_has_next_line(input, &next_i))
	{
		if (!input_read(input, shell))
			input->abort = 1;
	}
	if (input->abort)
		*line = NULL;
	else
		*line = ft_strndup(input->buffer->str, next_i);
	sbuffer_clear(input->buffer);
	if (!term_reset_mode(input->term))
		return (0);
	return (1);
}
