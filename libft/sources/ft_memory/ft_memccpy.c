/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 09:43:04 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:16:22 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*d_ptr;
	unsigned char	*s_ptr;
	unsigned char	symbol;

	d_ptr = (unsigned char *)dest;
	s_ptr = (unsigned char *)src;
	symbol = (unsigned char)c;
	while (n-- > 0)
	{
		*d_ptr++ = *s_ptr++;
		if (*(d_ptr - 1) == symbol)
			return (d_ptr);
	}
	return (NULL);
}
