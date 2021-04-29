/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/28 18:07:50 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"

t_env	*env_create(char const *represent[])
{
	t_env	*environment;
	int		i;

	i = -1;
	environment = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!environment)
		return (NULL);
	while (represent[++i] != NULL)
	{
		if (!ft_list_add(&(environment->collection),
				env_pair_from_str(represent[i])))
			return (NULL);
	}
	env_increment_shlvl(environment);
	env_list_sort(environment->collection);
	env_create_represent(environment,
		ft_list_count(environment->collection) + 1);
	return (environment);
}

int	env_update(t_env *env)
{
	env_list_sort(env->collection);
	return (env_create_represent(env, ft_list_count(env->collection) + 1));
}

int	env_destroy(t_env *env)
{
	void	(*ft_free_pair)(void *);
	void	(*ft_free)(void *);

	ft_free_pair = env_free_pair;
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

int	env_set(t_env *env, char const *key, char const *value)
{
	char	*old_value;
	t_pair	*pair;

	old_value = env_get_value(env, key);
	if (old_value == NULL)
	{
		if (!ft_list_add(&(env->collection), env_create_new_pair(key, value)))
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
		if (ft_strcmp(key, test->key) == 0)
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
	return (env_before_update(pair, env));
}
