/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 22:32:43 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 15:16:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack	*ft_stack_new(void *data)
{
	t_stack	*new_node;

	new_node = (t_stack *)ft_calloc(1, sizeof(t_stack));
	if (new_node == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->data = data;
	return (new_node);
}

int	ft_stack_push(t_stack **root, void *data)
{
	t_stack	*node;

	if (*root != NULL)
	{
		node = *root;
		*root = ft_stack_new(data);
		if (*root == NULL)
			return (0);
		(*root)->next = node;
	}
	else
	{
		*root = ft_stack_new(data);
		if (*root == NULL)
			return (0);
	}
	return (1);
}

void	*ft_stack_pop(t_stack **root)
{
	t_stack	*node;
	void	*data;

	data = NULL;
	if (root != NULL && *root != NULL)
	{
		node = *root;
		data = node->data;
		*root = node->next;
		free(node);
	}
	return (data);
}

void	*ft_stack_peek(t_stack *root)
{
	void	*data;

	data = NULL;
	if (root)
		data = root->data;
	return (data);
}

void	ft_stack_free(t_stack **root, void (*del)(void *))
{
	t_stack	*node;

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
