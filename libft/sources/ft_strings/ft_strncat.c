/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:49:53 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:45 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, char *src, size_t n)
{
	while (*dst)
		dst++;
	while (n-- > 0)
		*dst++ = *src++;
	*dst = '\0';
	return (dst);
}
