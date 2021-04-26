/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 09:45:05 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:16:20 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	unsigned char	symbol;

	s_ptr = (unsigned char *)s;
	symbol = (unsigned char)c;
	while (n-- > 0)
	{
		if (*s_ptr == symbol)
			return (s_ptr);
		s_ptr++;
	}
	return (NULL);
}
