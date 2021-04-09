/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:16:54 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:19:21 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(unsigned int value, int base)
{
	size_t len;

	len = 1;
	while (value /= base)
		len++;
	return (len);
}

char			*ft_utoa_base_lw(unsigned int value, int base, size_t wight)
{
	char	*result;
	size_t	len;

	result = NULL;
	if (wight > (len = num_len(value, base)))
		len = wight;
	if (!(result = (char *)ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = ft_digit_char_lw(value % base);
		value /= base;
	}
	return (result);
}

char			*ft_utoa_base_up(unsigned int value, int base, size_t wight)
{
	char	*result;
	size_t	len;

	result = NULL;
	if (wight > (len = num_len(value, base)))
		len = wight;
	if (!(result = (char *)ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	result[len] = '\0';
	while (len > 0)
	{
		result[--len] = ft_digit_char_up(value % base);
		value /= base;
	}
	return (result);
}
