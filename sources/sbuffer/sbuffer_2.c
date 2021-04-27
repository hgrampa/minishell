/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbuffer_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:16:31 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 11:02:28 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "sbuffer.h"
#include "errors.h"

int	sbuffer_clear(t_sbuffer *buffer)
{
	ft_bzero(buffer->str, buffer->size);
	buffer->len = 0;
	return (1);
}

int	sbuffer_backspace(t_sbuffer *buffer)
{
	if (buffer->len > 0)
	{
		buffer->len--;
		buffer->str[buffer->len] = '\0';
	}
	return (1);
}
