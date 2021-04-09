/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 09:46:05 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:16:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d_ptr;
	unsigned char	*s_ptr;

	if (dest == NULL && src == NULL)
		return (NULL);
	d_ptr = (unsigned char *)dest;
	s_ptr = (unsigned char *)src;
	while (n-- > 0)
		*d_ptr++ = *s_ptr++;
	return (dest);
}
