/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/24 13:25:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "environment.h"
#include "exit_code.h"

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
	if (env->exit_code != NULL)
		free(env->exit_code);
	free(env);
	return (1);
}

int	get_value_from_key(t_pair *pair, char const *key)
{
	return (ft_strcmp(pair->key, key));
}

// TODO можно оставить числовое предмтавление и менять только если реально изменится
char	*env_get_exit_code(t_env *env)
{
	if (env->exit_code != NULL)
		free(env->exit_code);
	env->exit_code = ft_itoa(exit_code_get());
	return (env->exit_code);
}

char	*env_get_value(t_env *env, char const *key)
{
	t_list	*lst;
	t_pair	*pair;

	if (ft_strncmp(key, "?", 1) == 0)
		return (env_get_exit_code(env));
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
