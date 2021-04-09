/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:53:14 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:54 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	if (*needle == '\0')
		return (hay);
	while (*hay && len-- > 0)
	{
		if (*hay == needle[i])
			i++;
		else
		{
			len += i;
			hay -= i;
			i = 0;
		}
		if (needle[i] == '\0')
			return (hay - i + 1);
		hay++;
	}
	return (NULL);
}
