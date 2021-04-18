/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/11 12:04:05 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include <stdio.h>

void	print_represent(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		printf("%s\n", array[i++]);
}

void	print_list(t_list *lst)
{
	t_pair	*pair;
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		pair = tmp->data;
		printf("%s=", pair->key);
		printf("\"%s\"\n", pair->value);
		tmp = tmp->next;
	}
}

void	free_pair(void *ptr)
{
	t_pair	*pair;

	pair = ptr;
	free(pair->key);
	pair->key = NULL;
	free(pair->value);
	pair->value = NULL;
}

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
}

int	compare_pairs(t_list *elem_cmp, t_list *temp_elem)
{
	t_pair	*data_pair;
	t_pair	*elem_pair;

	data_pair = (t_pair *)elem_cmp->data;
	elem_pair = (t_pair *)temp_elem->data;
	return (ft_strncmp(data_pair->key, elem_pair->key, 30) < 0);
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
