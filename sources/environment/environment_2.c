/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/11 12:04:05 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include "../../includes/environment.h"
#include <stdio.h>

int	env_update(t_env *env)
{
	ft_list_sort(env->collection);
	return (create_represent(env, ft_list_count(env->collection) + 1));
}

int	env_destroy(t_env *env)
{
	void	(*ft_free_pair)(void *);
	void	(*ft_free)(void *);

	ft_free_pair = free_pair;
	ft_free = free;
	ft_list_foreach(env->collection, ft_free_pair);
	ft_lstclear(&env->collection, ft_free);
	free_array(env->represent);
	free(env->collection);
	free(env->represent);
	free(env);
	return (1);
}

int	get_value_from_key(t_pair *pair, char const *key)
{
	return (ft_strncmp(pair->key, key, 30));
}

char	*env_get_value(t_env *env, char const *key)
{
	t_list	*lst;
	t_pair	*pair;

	lst = env->collection;
	while (lst != NULL)
	{	
		if (get_value_from_key(lst->data, key) == 0)
		{
			pair = lst->data;
			return (pair->value);
		}
		lst = lst->next;
	}
	return (NULL);
}

t_pair	*env_get_pair(t_env *env, char const *key)
{
	t_list	*lst;
	t_pair	*pair;

	lst = env->collection;
	while (lst != NULL)
	{	
		if (get_value_from_key(lst->data, key) == 0)
		{
			pair = lst->data;
			return (lst->data);
		}
		lst = lst->next;
	}
	return (NULL);
}
