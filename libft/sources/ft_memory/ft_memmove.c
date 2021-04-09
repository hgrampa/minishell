/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:44:02 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:16:11 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d_ptr;
	unsigned char	*s_ptr;

	if (dest == NULL && src == NULL)
		return (NULL);
	d_ptr = (unsigned char *)dest;
	s_ptr = (unsigned char *)src;
	if (dest < src)
	{
		while (n-- > 0)
			*d_ptr++ = *s_ptr++;
	}
	else
	{
		d_ptr += n;
		s_ptr += n;
		while (n-- > 0)
			*--d_ptr = *--s_ptr;
	}
	return (dest);
}
