/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbuffer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:16:31 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:54:00 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sbuffer.h"
#include "errors.h"

static int	sbuffer_realloc(t_sbuffer *buffer, size_t rec_size)
{
	size_t	count;
	size_t	new_size;
	char	*ptr;

	count = rec_size / buffer->step + 1;
	new_size = buffer->step * count;
	ptr = buffer->str;
	buffer->str = (char *)ft_calloc(1, new_size);
	if (buffer->str == NULL)
		return (err_print(NULL, 0, 1));
	ft_memcpy(buffer->str, ptr, buffer->size);
	free(ptr);
	buffer->size = new_size;
	return (1);
}

t_sbuffer	*sbuffer_create(size_t step)
{
	t_sbuffer	*buffer;

	buffer = (t_sbuffer *)ft_calloc(1, sizeof(t_sbuffer));
	if (buffer == NULL)
		return (NULL);
	buffer->str = (char *)ft_calloc(step, sizeof(char));
	if (buffer->str == NULL)
	{
		free(buffer);
		return (NULL);
	}
	buffer->step = step;
	buffer->size = step;
	return (buffer);
}

int	sbuffer_destroy(t_sbuffer *buffer)
{
	if (buffer->str != NULL)
		free(buffer->str);
	free(buffer);
	return (1);
}

int	sbuffer_add_str(t_sbuffer *buffer, char *str)
{
	size_t	i;
	size_t	str_len;
	size_t	rec_size;
	char	*buff_end;

	str_len = ft_strlen(str);
	rec_size = (str_len + buffer->len) * sizeof(char);
	if (rec_size >= buffer->size)
	{
		if (!sbuffer_realloc(buffer, rec_size))
			return (0);
	}
	buff_end = &(buffer->str[buffer->len]);
	i = -1;
	while (++i < str_len)
		buff_end[i] = str[i];
	buffer->len += str_len;
	return (1);
}

int	sbuffer_add_char(t_sbuffer *buffer, char c)
{
	size_t	rec_size;
	char	*buff_end;

	rec_size = (buffer->len + 1) * sizeof(char);
	if (rec_size >= buffer->size)
	{
		if (!sbuffer_realloc(buffer, rec_size))
			return (0);
	}
	buff_end = &(buffer->str[buffer->len]);
	*buff_end = c;
	buffer->len += 1;
	return (1);
}
