/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:22:58 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/24 22:24:24 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	int				c;

	i = 0;
	if (!s1 || !s2)
		return (s1 == s2);
	while (s1[i] || s2[i])
	{
		c = (unsigned char)s1[i] - (unsigned char)s2[i];
		if (c)
			return (c);
		i++;
	}
	return (0);
}
