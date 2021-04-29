/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_pathfinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:10:40 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 13:18:18 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"
#include <sys/types.h>
#include <sys/stat.h>

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

int	is_file_exists(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == -1)
		return (0);
	return (1);
}

int	is_directory(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

int	has_execute_permission(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == 0 && stats.st_mode & S_IXUSR)
		return (1);
	return (0);
}

int	check_executable(char *path)
{
	printf("path %s\n", path);
	if (path == NULL)
		return (1);
	if (is_directory(path))
	{
		printf(": is a directory\n");
		return (126);
	}
	else if (!is_file_exists(path))
	{
		printf("No such file or directory\n");
		return (127);
	}
	else if (!has_execute_permission(path))
	{
		printf("Permission denied\n");
		return (126);
	}
	return (0);
}

char	*factory_find_path(t_factory *factory, char *bin)
{
	char	*path;
	int	is_exec;

	is_exec = 0;
	if (bin == NULL)
		return (NULL);
	if (bin[0] == '\0')
		return (NULL);
	if (check_abs_path(bin))
		path = find_required_abs_path(bin);
	if (factory->paths == NULL)
		return (NULL);
	else
		path = find_required_rel_path(factory->paths, bin);
	is_exec = check_executable(bin);
	if (is_exec != 0)
		return (NULL);
	return (path);
}
