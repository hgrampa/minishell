/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:39:14 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/20 11:37:12 by hgrampa          ###   ########.fr       */
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

int	ft_dlist_pull(t_dlist **root, void *data)
{
	t_dlist	*new_node;

	new_node = ft_dlist_new(data);
	if (new_node == NULL)
		return (0);
	if (*root != NULL)
	{
		new_node->next = *root;
		(*root)->previous = new_node;
	}
	*root = new_node;
	return (1);
}

void	ft_dlist_free(t_dlist **root, void (*del)(void*))
{
	t_dlist	*node;

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

int	ft_dlist_add(t_dlist **root, void *data)
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
		*root = ft_dlist_new(data);
		if (*root == NULL)
			return (0);
	}
	return (1);
}
