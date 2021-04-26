/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:13:57 by hgrampa           #+#    #+#             */
/*   Updated: 2021/01/19 16:26:37 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_queue	*ft_queue_new(void *data)
{
	t_queue	*new_node;

	new_node = (t_queue *)ft_calloc(1, sizeof(t_queue));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->data = data;
	return (new_node);
}

int	ft_queue_enqueue(t_queue **root, void *data)
{
	t_queue	*node;

	if (*root != NULL)
	{
		node = *root;
		while (node->next != NULL)
			node = node->next;
		node->next = ft_queue_new(data);
		if (node->next == NULL)
			return (0);
	}
	else
	{
		*root = ft_queue_new(data);
		if (*root == NULL)
			return (0);
	}
	return (1);
}

void	*ft_queue_dequeue(t_queue **root)
{
	t_queue	*node;
	void	*data;

	data = NULL;
	if (root && *root)
	{
		node = *root;
		data = node->data;
		*root = node->next;
		free(node);
	}
	return (data);
}

void	*ft_queue_peek(t_queue *root)
{
	void	*data;

	data = NULL;
	if (root)
		data = root->data;
	return (data);
}

void	ft_queue_free(t_queue **root, void (*del)(void *))
{
	t_queue	*node;

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
