/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:54:11 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/18 15:54:14 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include  <fcntl.h>
#include "libft.h"
#include "environment.h"

char	*ft_concat3(char *str1, char *str2, char *str3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*tmp;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	len3 = ft_strlen(str3);
	result = (char *)ft_calloc(len1 + len2 + len3 + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	tmp = result;
	ft_strncat(tmp, str1, len1);
	tmp += len1;
	ft_strncat(tmp, str2, len2);
	tmp += len2;
	ft_strncat(tmp, str3, len3);
	return (result);
}

char	*find_required_rel_path(char **path_array, char *str)
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

int	check_abs_path(char *str)
{
	while (*str)
	{
		if (*str++ == '/')
			return (1);
	}
	return (0);
}

char	*find_required_abs_path(char *str)
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

int	main(int ac, char **av, char const **env)
{
	t_env	*environment;
	char	*required_path;
	char	**path_array;
	char	*path;

	if (ac == 2)
	{
		environment = env_create(env);
		if (check_abs_path(av[1]))
			required_path = find_required_abs_path(av[1]);
		else
		{
			path = env_get_value(environment, "PATH");
			path_array = ft_split(path, ':');
			required_path = find_required_rel_path(path_array, av[1]);
			free_array(path_array);
		}
		printf("required_path = %s\n", required_path);
		free(required_path);
		env_destroy(environment);
	}
	return (0);
}
