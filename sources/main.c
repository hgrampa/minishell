
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/11 12:04:05 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include "environment.h"
# include <stdio.h>

void	ft_list_sort(t_list *elem)
{
	t_list *temp_data;
	t_list *temp_elem;
	t_list *elem_cmp;
	t_pair *elem_cmp_data_pair;
	t_pair *temp_elem_pair;

	while (elem->next != NULL)
	{
		temp_data = elem->data;
		temp_elem = elem;
		elem_cmp = elem->next;
		while (elem_cmp != NULL)
		{
			elem_cmp_data_pair = (t_pair*)elem_cmp->data;
			temp_elem_pair = (t_pair*)temp_elem->data;
			if (ft_strncmp(elem_cmp_data_pair->key, temp_elem_pair->key, 30) < 0)
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

void print_list(t_list *lst)
{
	t_pair *pair;

	while (lst != NULL)
	{
		pair = (t_pair*)lst->data;
		printf("%s\n", pair->key);
		lst = lst->next;
	}
}

int main(int ac, char **av, const char **env)
{
	t_env *environment;
	

	printf("%d\n", ac);
	printf("%s\n", av[0]);
	environment = env_create(env);
	printf("________________\n");
	ft_list_sort(environment->collection);
	print_list(environment->collection);
	return (1);
}