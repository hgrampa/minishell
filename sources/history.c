/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 19:23:29 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/15 19:59:47 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_history
{
	t_list	*root;
	t_list	*carriage;
}				t_history;

t_history		*history_create()
{
	t_history *history;

	history =  (t_history *)ft_calloc(1, sizeof(t_history));
	if (history == NULL)
		return (NULL);
	history->root = NULL;
	history->carriage = NULL;
	return (history);
}


int				history_serealize(t_history *history)
{
	
}

int				history_deserealize(t_history *history)
{
	
}

int				history_destroy(t_history *history)
{
	if (history == NULL)
	{
		ft_list_free(&history->root, free);
		history->carriage = NULL;
		free(history);
	}
	return (1);
}
 
int		history_add(t_history *history, char *str)
{
	if (!ft_list_add_font(&history->root, str))
		return (0);
	// carriage - newest
	history->carriage = history->root;
}

char *history_up(t_history *history)
{
	char	*result;

	if (history->carriage == NULL)
		return (NULL);
	result = (char *)history->carriage->data;
	if (history->carriage->next == NULL)
		write(0, "\a", 1);
	else
		history->carriage = history->carriage->next;
	return(result);
}

char *history_down(t_history *history)
{
	char	*result;

	if (history->carriage == NULL)
		return (NULL);
	if (history->carriage->previous != NULL)
	{
		history->carriage = history->carriage->previous;
		result = history->carriage->data; 
	}
	return (result);
}

