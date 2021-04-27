/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 12:41:12 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:08 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(int value, size_t *sign, int base)
{
	size_t	len;

	if (value < 0)
		*sign = 1;
	else
		*sign = 0;
	len = 1;
	value /= base;
	while (value > 0)
	{
		len++;
		value /= base;
	}
	return (len);
}

char	*ft_itoa_base_lw(int value, int base, size_t wight)
{
	char	*result;
	size_t	sign;
	size_t	len;

	if (base == 10 && value == _FT_SINT32_LAST)
		return (ft_strdup(_FT_SINT32_LAST_STR));
	len = num_len(value, &sign, base);
	if (wight > len)
		len = wight;
	result = (char *)ft_calloc(len + sign + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (sign)
	{
		value *= -1;
		result[0] = '-';
		len++;
	}
	result[len] = '\0';
	while (len > sign)
	{
		result[--len] = ft_digit_char_lw(value % base);
		value /= base;
	}
	return (result);
}

char	*ft_itoa_base_up(int value, int base, size_t wight)
{
	char	*result;
	size_t	sign;
	size_t	len;

	result = NULL;
	if (base == 10 && value == _FT_SINT32_LAST)
		return (ft_strdup(_FT_SINT32_LAST_STR));
	len = num_len(value, &sign, base);
	if (wight > len)
		len = wight;
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	if (sign)
	{
		value *= -1;
		result[0] = '-';
	}
	result[len] = '\0';
	while (len > sign)
	{
		result[--len] = ft_digit_char_up(value % base);
		value /= base;
	}
	return (result);
}
