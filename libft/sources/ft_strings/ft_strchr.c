/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:44:30 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:18 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_ptr;
	char	cch;

	s_ptr = (char *)s;
	cch = (char)c;
	while (*s_ptr != '\0')
	{
		if (*s_ptr == cch)
			return (s_ptr);
		s_ptr++;
	}
	if (*s_ptr == cch)
		return (s_ptr);
	else
		return (NULL);
}
