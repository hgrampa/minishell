/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:54:23 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:36 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	size;

	size = 0;
	if (!dst || !src)
		return (0);
	while (src[size] != '\0')
		size++;
	if (dstsize == 0)
		return (size);
	while (*src && dstsize-- > 1)
		*dst++ = *src++;
	*dst = '\0';
	return (size);
}
