/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 19:23:29 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/21 15:15:03 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

t_history	*history_create(void)
{
	t_history *history;

	history = (t_history *)ft_calloc(1, sizeof(t_history));
	if (history == NULL)
		return (NULL);
	history->root = NULL;
	history->carriage = NULL;
	return (history);
}

int			history_init(t_history *history)
{
	history_deserealize(history); // пофигу на результат
	return (1);
}

int			history_serealize(t_history *history)
{
	int		fd;
	t_dlist	*root;

	root = history->root;
	fd = open(_HISTORY_FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd)
	{
		while (root != NULL)
		{
			write(fd, root->data, ft_strlen(root->data));
			write(fd, "\n", 1);
			root = root->next;
		}
	}
	else
		return (0);
	close(fd);
	return (1);
}

int			history_deserealize(t_history *history)
{
	int		fd;
	int		result;
	char	*line;

	fd = open(_HISTORY_FILE_NAME, O_RDONLY);
	if (fd < 0)
	{
		printf("Fail to open the history file\n"); // TODO возврат ошибки (или тотальный игнор)
		return (0);
	}
	line = NULL;
	result = ft_gnl(fd, &line, _HISTORY_READ_BUFF_SIZE);
	while (result > 0)
	{
		// TODO подумать над тем что бы убрать лишнее дублирование
		ft_dlist_add(&history->root, ft_strdup(line));
		free(line);
		result = ft_gnl(fd, &line, _HISTORY_READ_BUFF_SIZE);
	}
	// TODO эта строка тип последняя?
	ft_dlist_add(&history->root, ft_strdup(line));
	free(line);
	close(fd);
	return (1);
}

int			history_destroy(t_history *history)
{
	// TODO можно тут сохранять
	ft_dlist_free(&history->root, free);
	history->carriage = NULL;
	free(history);
	return (1);
}

int			history_add(t_history *history, char *str)
{	
	history->carriage = NULL;
	if (ft_strlen(str) == 0)
		return (1);
	if (!ft_dlist_pull(&history->root, str))
		return (0);
	return(1);
}

char		*history_up(t_history *history)
{
	char	*result;

	if (history->carriage == NULL)
	{
		if (history->root != NULL)
		{
			history->carriage = history->root;
			result = (char *)history->carriage->data;
			return(result);
		}
		return(NULL);
	}
	else if (history->carriage->next != NULL)
	{
		history->carriage = history->carriage->next;
		result = (char *)history->carriage->data;
		return(result);
	}
	return(NULL);
}

char		*history_down(t_history *history)
{
	char	*result;

	if (history->carriage == NULL)
		return (NULL);
	if (history->carriage->previous != NULL)
	{
		history->carriage = history->carriage->previous;
		result = (char *)history->carriage->data;
		return(result);
	}
	else
		history->carriage = NULL;
	return (NULL);
}
