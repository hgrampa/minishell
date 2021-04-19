/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:39:14 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/19 20:35:20 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

t_dlist	*ft_dlist_new(void *data)
{
	t_dlist	*new_node;

	new_node = (t_dlist *)ft_calloc(1, sizeof(t_dlist));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->previous = NULL;
	new_node->data = data;
	return (new_node);
}

int		ft_dlist_pull(t_dlist **root, t_dlist *new_dlist)
{
	t_dlist *old_dlist;

	old_dlist = *root;
	if (root && new_dlist)
	{
		if (*root)
			new_dlist->next = *root;
		old_dlist->previous = new_dlist;
	}
	return (1);
}

void	ft_dlist_free(t_dlist **root, void (*del)(void*))
{
	t_dlist *node;

	if (del != NULL)
	{
		while (*root != NULL)
		{
			node = *root;
			del(node->data);
			*root = node->next;
			free(node);
		}
	}
	else
	{
		while (*root != NULL)
		{
			node = *root;
			*root = node->next;
			free(node->data);
			free(node);
		}
	}
}

void	ft_dlist_foreach(t_dlist *root, void (*f)(void *))
{
	while (root != NULL)
	{
		f(root->data);
		root = root->next;
	}
}

int		ft_dlist_add(t_dlist **root, void *data)
{
	t_dlist	*node;
	t_dlist	*new_node;

	if (*root != NULL)
	{
		node = *root;
		while (node->next != NULL)
			node = node->next;
		node->next = ft_dlist_new(data);
		new_node = node->next;
		new_node->previous = node;
		if (node->next == NULL)
			return (0);
	}
	else
	{
		if ((*root = ft_dlist_new(data)) == NULL)
			return (0);
	}
	return (1);
}
