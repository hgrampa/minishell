/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:56:32 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:35:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

int	history_serealize(t_history *history)
{
	int		fd;
	t_dlist	*root;

	root = history->root;
	if (root == NULL)
		return (0);
	fd = open(_HISTORY_FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd)
	{
		write(fd, root->data, ft_strlen(root->data));
		root = root->next;
		while (root != NULL)
		{
			write(fd, "\n", 1);
			write(fd, root->data, ft_strlen(root->data));
			root = root->next;
		}
	}
	else
		return (0);
	close(fd);
	return (1);
}

int	history_deserealize(t_history *history)
{
	int		fd;
	int		result;
	char	*line;

	fd = open(_HISTORY_FILE_NAME, O_RDONLY);
	if (fd < 0)
		return (1);
	line = NULL;
	result = ft_gnl(fd, &line, _HISTORY_READ_BUFF_SIZE);
	while (result > 0)
	{
		ft_dlist_add(&history->root, line);
		result = ft_gnl(fd, &line, _HISTORY_READ_BUFF_SIZE);
		if (result == -1)
		{
			free(line);
			close(fd);
			return (0);
		}
	}
	ft_dlist_add(&history->root, ft_strdup(line));
	free(line);
	close(fd);
	return (1);
}

char	*history_up(t_history *history)
{
	char	*result;

	if (history->carriage == NULL)
	{
		if (history->root != NULL)
		{
			history->carriage = history->root;
			result = (char *)history->carriage->data;
			return (result);
		}
		return (NULL);
	}
	else if (history->carriage->next != NULL)
	{
		history->carriage = history->carriage->next;
		result = (char *)history->carriage->data;
		return (result);
	}
	return (NULL);
}

char	*history_down(t_history *history)
{
	char	*result;

	if (history->carriage == NULL)
		return (NULL);
	if (history->carriage->previous != NULL)
	{
		history->carriage = history->carriage->previous;
		result = (char *)history->carriage->data;
		return (result);
	}
	else
		history->carriage = NULL;
	return (NULL);
}
