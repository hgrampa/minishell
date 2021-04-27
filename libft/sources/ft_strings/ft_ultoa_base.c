/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:51:30 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:19:19 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(unsigned long value, int base)
{
	size_t	len;

	len = 1;
	value /= base;
	while (value > 0)
	{
		len++;
		value /= base;
	}
	return (len);
}

char	*ft_ultoa_base_lw(unsigned long value, int base, size_t wight)
{
	char	*result;
	size_t	len;

	result = NULL;
	len = num_len(value, base);
	if (wight > len)
		len = wight;
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = ft_digit_char_lw(value % base);
		value /= base;
	}
	return (result);
}

char	*ft_ultoa_base_up(unsigned long value, int base, size_t wight)
{
	char	*result;
	size_t	len;

	result = NULL;
	len = num_len(value, base);
	if (wight > len)
		len = wight;
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = ft_digit_char_up(value % base);
		value /= base;
	}
	return (result);
}
