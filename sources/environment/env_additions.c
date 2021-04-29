/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_additions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/28 17:45:23 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"

t_list	*env_get_previous_pair(t_env *env, char const *key)
{
	t_list	*lst;
	t_list	*tmp;

	tmp = NULL;
	lst = env->collection;
	while (lst != NULL)
	{	
		if (env_get_value_from_key(lst->data, key) == 0)
			return (tmp);
		tmp = lst;
		lst = lst->next;
	}
	return (NULL);
}

int	env_before_update(t_list *pair, t_env *env)
{
	env_free_pair(pair->data);
	free(pair->data);
	free(pair);
	pair = NULL;
	if (!env_update(env))
		return (0);
	return (1);
}

void	env_increment_shlvl(t_env *env)
{
	t_pair	*shlvl_pair;
	int		level;

	shlvl_pair = env_get_pair(env, _ENV_SHLVL);
	if (shlvl_pair != NULL)
	{
		level = ft_atoi(shlvl_pair->value);
		level++;
		free(shlvl_pair->value);
		if (level == 1000)
			shlvl_pair->value = ft_strdup(_ENV_SHLVL_EMPY);
		else if (level == 1001)
			shlvl_pair->value = ft_strdup(_ENV_SHLVL_DEFAULT);
		else
			shlvl_pair->value = ft_itoa(level);
	}
}

int	env_isname_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

void	env_list_sort(t_list *elem)
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
			if (env_compare_pairs(elem_cmp, temp_elem))
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
