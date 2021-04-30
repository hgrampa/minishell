/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/30 12:44:08 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "environment.h"
#include "exit_code.h"

int	env_get_value_from_key(t_pair *pair, char const *key)
{
	return (ft_strcmp(pair->key, key));
}

char	*env_get_exit_code(t_env *env)
{
	if (env->exit_code != NULL)
		free(env->exit_code);
	env->exit_code = ft_itoa(exit_code_take());
	return (env->exit_code);
}

char	*env_get_value(t_env *env, char const *key)
{
	t_list	*lst;
	t_pair	*pair;

	if (key[0] == '?')
		return (env_get_exit_code(env));
	lst = env->collection;
	while (lst != NULL)
	{	
		if (env_get_value_from_key(lst->data, key) == 0)
		{
			pair = lst->data;
			return (pair->value);
		}
		lst = lst->next;
	}
	return (NULL);
}
