/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:53:39 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:47 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned char	*s_ptr1;
	unsigned char	*s_ptr2;

	s_ptr1 = (unsigned char *)s1;
	s_ptr2 = (unsigned char *)s2;
	while ((*s_ptr1 != '\0' || *s_ptr2 != '\0') && n-- > 0)
	{
		if (*s_ptr1 != *s_ptr2)
			return (*s_ptr1 - *s_ptr2);
		s_ptr1++;
		s_ptr2++;
	}
	return (0);
}
