/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:43:08 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:04 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_numlen(size_t *signature, int n)
{
	size_t	size;

	*signature = (n < 0);
	size = 1;
	n /= 10;
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;
	size_t	signature;

	if (n == _FT_SINT32_LAST)
		return (ft_strdup(_FT_SINT32_LAST_STR));
	len = ft_numlen(&signature, n);
	result = (char *)malloc(sizeof(char) * (len + signature + 1));
	if (!result)
		return (NULL);
	if (signature != 0)
	{
		n *= -1;
		result[0] = '-';
		len++;
	}
	result[len] = '\0';
	while (len > signature)
	{
		result[--len] = (n % 10) + _FT_ASCII_NUM_OFFSET;
		n /= 10;
	}
	return (result);
}
