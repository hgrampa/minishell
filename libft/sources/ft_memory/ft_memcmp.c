/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 09:45:50 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:16:17 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	int				result;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	result = 0;
	while (n-- > 0)
	{
		result = *s1_ptr++ - *s2_ptr++;
		if (result != 0)
			return (result);
	}
	return (0);
}
