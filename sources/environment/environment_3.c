/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/16 14:48:48 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"

t_pair	*create_new_pair(char const *key, char const *value)
{
	t_pair	new_pair;
	t_pair	*new_pair_ptr;

	new_pair.key = ft_strdup(key);
	if (value == NULL)
		new_pair.value = NULL;
	else
		new_pair.value = ft_strdup(value);
	new_pair_ptr = (t_pair *)ft_calloc(1, sizeof(t_pair));
	*new_pair_ptr = new_pair;
	return (new_pair_ptr);
}

int	env_set(t_env *env, char const *key, char const *value)
{
	char	*old_value;
	t_pair	*pair;

	old_value = env_get_value(env, key);
	if (old_value == NULL)
	{
		if (!ft_list_add(&(env->collection), create_new_pair(key, value)))
			return (0);
	}
	else
	{
		pair = env_get_pair(env, key);
		free(pair->value);
		if (value != NULL)
			pair->value = ft_strdup(value);
		else
			pair->value = NULL;
	}
	if (!env_update(env))
		return (0);
	return (1);
}

t_list	*env_get_previous_pair(t_env *env, char const *key)
{
	t_list	*lst;
	t_list	*tmp;

	tmp = NULL;
	lst = env->collection;
	while (lst != NULL)
	{	
		if (get_value_from_key(lst->data, key) == 0)
			return (tmp);
		tmp = lst;
		lst = lst->next;
	}
	return (NULL);
}

static int	continue_unseting_fck_norm(t_list *pair, t_env *env)
{
	free_pair(pair->data);
	free(pair->data);
	free(pair);
	pair = NULL;
	if (!env_update(env))
		return (0);
	return (1);
}

int	env_unset(t_env *env, char const *key)
{
	t_list	*previous_pair;
	t_list	*pair;
	t_pair	*test;

	previous_pair = env_get_previous_pair(env, key);
	if (previous_pair == NULL)
	{
		pair = env->collection;
		test = pair->data;
		if (ft_strncmp(key, test->key, 30) == 0)
		{
			pair = env->collection;
			env->collection = env->collection->next;
		}
		else
			return (0);
	}
	else
	{
		pair = previous_pair->next;
		previous_pair->next = pair->next;
	}
	return (continue_unseting_fck_norm(pair, env));
}
