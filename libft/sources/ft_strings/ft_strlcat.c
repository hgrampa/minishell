/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:44:38 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:33 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	dstlen;
	size_t	result;

	srcsize = ft_strlen(src);
	dstlen = 0;
	while (*dst != '\0')
	{
		dst++;
		dstlen++;
	}
	if (dstlen < dstsize)
		result = dstlen + srcsize;
	else
		result = dstsize + srcsize;
	if (dstsize == 0)
		return (result);
	while (*src && dstlen < --dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (result);
}
