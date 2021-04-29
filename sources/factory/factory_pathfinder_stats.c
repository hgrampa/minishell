/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_pathfinder_stats.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 19:12:51 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 20:40:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"
#include <sys/types.h>
#include <sys/stat.h>

static int	is_directory(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == 0 && S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

static int	has_execute_permission(char *path)
{
	struct stat		stats;

	if (stat(path, &stats) == 0 && stats.st_mode & S_IXUSR)
		return (1);
	return (0);
}

char	*factory_check_path(char *path, char *name)
{
	if (is_directory(path))
	{
		free(path);
		path = NULL;
		err_print_object(name, _ERR_ISDIR, 126, 0);
	}
	else if (!has_execute_permission(path))
	{
		free(path);
		path = NULL;
		err_print_object(name, _ERR_PERMDEN, 126, 0);
	}
	return (path);
}
