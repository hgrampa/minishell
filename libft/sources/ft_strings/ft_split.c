/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:44:17 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:10 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_tablen(char const *s, char c)
{
	size_t			tablen;
	unsigned char	dirty;

	tablen = 0;
	dirty = '\1';
	while (*s != '\0')
	{
		if (*s == c && dirty == 0)
			dirty = '\1';
		else if (*s != c && dirty == 1)
		{
			tablen++;
			dirty = '\0';
		}
		s++;
	}
	return (tablen);
}

static size_t	get_strlen(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (*s != '\0' && *s++ != c)
		size++;
	return (size);
}

static void	*clean_all(char **table, unsigned int topidex)
{
	while (topidex != 0)
	{
		free(table[topidex]);
		table[topidex--] = NULL;
	}
	free(table);
	table = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	char			**result;
	size_t			table_size;
	size_t			str_size;

	if (!s)
		return (NULL);
	table_size = get_tablen(s, c) + 1;
	result = (char **)malloc(sizeof(char *) * table_size);
	if (!result)
		return (NULL);
	i = 0;
	while (*s && --table_size > 0)
	{
		while (*s == c)
			s++;
		str_size = get_strlen(s, c) + 1;
		result[i] = (char *)malloc(sizeof(char) * str_size);
		if (!result[i])
			return (clean_all(result, i));
		ft_strlcpy(result[i++], s, str_size);
		s += --str_size;
	}
	result[i] = NULL;
	return (result);
}
