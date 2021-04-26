/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:42:20 by hgrampa           #+#    #+#             */
/*   Updated: 2021/01/19 16:25:49 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_new(void *data)
{
	t_list	*new_node;

	new_node = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->data = data;
	return (new_node);
}

int	ft_list_add(t_list **root, void *data)
{
	t_list	*node;

	if (*root != NULL)
	{
		node = *root;
		while (node->next != NULL)
			node = node->next;
		node->next = ft_list_new(data);
		if (node->next == NULL)
			return (0);
	}
	else
	{
		*root = ft_list_new(data);
		if (*root == NULL)
			return (0);
	}
	return (1);
}

int	ft_list_count(t_list *root)
{
	int	count;

	count = 0;
	while (root != NULL)
	{
		count++;
		root = root->next;
	}
	return (count);
}

void	ft_list_foreach(t_list *root, void (*f)(void *))
{
	while (root != NULL)
	{
		f(root->data);
		root = root->next;
	}
}

void	ft_list_free(t_list **root, void (*del)(void*))
{
	t_list	*node;

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
			free(node);
		}
	}
}
