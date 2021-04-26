/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_tosa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:25:05 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 14:30:16 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**array_clear(char **array)
{
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
	free(array);
	return (NULL);
}

char	**ft_list_tosa(t_list *list)
{
	size_t	i;
	size_t	count;
	char	**array;

	count = ft_list_count(list);
	array = (char **)ft_calloc(count + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		array[i] = ft_strdup((char *)list->data);
		if (array == NULL)
			return (array_clear(array));
		list = list->next;
	}
	return (array);
}
