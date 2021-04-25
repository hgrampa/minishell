/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:52:12 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:19:09 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_chinstr(char const *s, char c)
{
	while (*s != '\0')
	{
		if (*s++ == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			begin_index;
	size_t			end_index;

	if (!s1 || !set)
		return (NULL);
	begin_index = 0;
	end_index = ft_strlen(s1);
	if (end_index > 0)
	{
		while (s1[begin_index] != '\0' && is_chinstr(set, s1[begin_index]))
			begin_index++;
		end_index--;
		while (end_index >= begin_index && is_chinstr(set, s1[end_index]))
			end_index--;
	}
	return (ft_substr(&s1[begin_index], 0, end_index - begin_index + 1));
}
