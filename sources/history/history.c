/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 19:23:29 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/26 19:10:00 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

t_history	*history_create(void)
{
	t_history	*history;

	history = (t_history *)ft_calloc(1, sizeof(t_history));
	if (history == NULL)
		return (NULL);
	history->root = NULL;
	history->carriage = NULL;
	return (history);
}

int	history_init(t_history *history)
{
	return (history_deserealize(history));
}

int	history_destroy(t_history *history)
{
	ft_dlist_free(&history->root, free);
	history->carriage = NULL;
	free(history);
	return (1);
}

int	history_add(t_history *history, char *str)
{	
	history->carriage = NULL;
	if (ft_strlen(str) == 0)
		return (1);
	if (!ft_dlist_pull(&history->root, str))
		return (0);
	return (1);
}
