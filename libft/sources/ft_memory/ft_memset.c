/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:44:05 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:16:04 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	unsigned char	symbol;

	s_ptr = (unsigned char *)s;
	symbol = (unsigned char)c;
	while (n-- > 0)
		*s_ptr++ = symbol;
	return (s);
}
