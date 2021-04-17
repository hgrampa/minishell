/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_lists.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:39:14 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/17 18:39:16 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlists.h"
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

int	ft_dlist_pull(t_dlist **root, t_dlist *new_dlist)
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

void ft_dlist_free(t_dlist **root, void (*del)(void*))
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
			free(node);
		}
	}
}

// int main()
// {
// 	t_dlist *test0;
// 	t_dlist *test1;
// 	t_dlist *test2;

// 	test2 = ft_dlist_new("789");
// 	test1 = ft_dlist_new("456");
// 	test0 = ft_dlist_new("123");
// 	ft_dlist_pull(&test1, test0);
// 	ft_dlist_pull(&test2, test1);
// 	// printf("%s\n", test0->next->data);
// 	// printf("%s\n", test2->previous->data);
// 	// printf("%s\n", test1->previous->data);
// 	// printf("%s\n", test0->data);
// 	ft_dlist_free(&test0, NULL);
// 	return(0);
// }