/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_pathfinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:10:40 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:34:57 by hgrampa          ###   ########.fr       */
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

static int	if_abs_rel_path(char *str)
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

static char	*bin_finder(t_factory *factory, char *name)
{
	char	*path;

	if (factory->paths == NULL)
		return (NULL);
	else
	{
		path = find_required_rel_path(factory->paths, name);
		if (path == NULL)
		{
			err_print_object(name, _ERR_NOCOMMAND, 127, 0);
			return (NULL);
		}
		return (factory_check_path(path, name));
	}
	return (path);
}

char	*factory_find_path(t_factory *factory, char *name)
{
	char	*path;

	if (name == NULL)
		return (NULL);
	if (name[0] == '\0')
		return (NULL);
	if (if_abs_rel_path(name))
	{
		path = find_required_abs_path(name);
		if (path == NULL)
		{
			err_print_object(name, NULL, 127, 0);
			return (NULL);
		}
		return (factory_check_path(path, name));
	}
	else
		return (bin_finder(factory, name));
}
