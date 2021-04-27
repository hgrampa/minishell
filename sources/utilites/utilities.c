/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_carray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:09:35 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 13:10:11 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			array[i++] = NULL;
		}
	}
	free(array);
}

static int	compare_pairs(t_list *elem_cmp, t_list *temp_elem)
{
	t_pair	*data_pair;
	t_pair	*elem_pair;

	data_pair = (t_pair *)elem_cmp->data;
	elem_pair = (t_pair *)temp_elem->data;
	return (ft_strcmp(data_pair->key, elem_pair->key) < 0);
}

void	ft_list_sort(t_list *elem)
{
	t_list	*temp_data;
	t_list	*temp_elem;
	t_list	*elem_cmp;

	while (elem->next != NULL)
	{
		temp_data = elem->data;
		temp_elem = elem;
		elem_cmp = elem->next;
		while (elem_cmp != NULL)
		{
			if (compare_pairs(elem_cmp, temp_elem))
			{
				temp_data = elem_cmp->data;
				temp_elem = elem_cmp;
			}
			elem_cmp = elem_cmp->next;
		}
		temp_elem->data = elem->data;
		elem->data = temp_data;
		elem = elem->next;
	}
}
