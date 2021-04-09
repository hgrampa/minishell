/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:53:02 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:19:06 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	char	symbol;

	result = (char *)s + ft_strlen(s);
	symbol = (char)c;
	while (result >= s)
	{
		if (*result == symbol)
			return (result);
		result--;
	}
	return (NULL);
}
