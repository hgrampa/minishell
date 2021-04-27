/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_pathfinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:10:40 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 21:29:45 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"

static char	*find_required_rel_path(char **path_array, char *str)
{
	int		fd;
	char	*path_str;
	int		i;

	i = -1;
	while (path_array[++i] != 0)
	{
		path_str = ft_concat3(path_array[i], "/", str);
		fd = open(path_str, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			return (path_str);
		}
		free(path_str);
	}
	return (NULL);
}

// TODO Добавить ../ ./
static int	check_abs_path(char *str)
{
	while (*str)
	{
		if (*str++ == '/')
			return (1);
	}
	return (0);
}

static char	*find_required_abs_path(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (ft_strdup(str));
	}
	return (NULL);
}

char *factory_find_path(t_factory *factory, char *bin)
{
	char *path;

	if (bin == NULL)
		return (NULL);
	if (bin[0] == '\0')
		return (NULL);
	if (factory->paths == NULL)
		return (NULL);
	if (check_abs_path(bin))
		path = find_required_abs_path(bin);
	else
		path = find_required_rel_path(factory->paths, bin);
	return(path);
}
