/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pair.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:52:07 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/28 17:44:53 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"

t_pair	*env_create_new_pair(char const *key, char const *value)
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

void	env_free_pair(void *ptr)
{
	t_pair	*pair;

	pair = ptr;
	free(pair->key);
	pair->key = NULL;
	free(pair->value);
	pair->value = NULL;
}

t_pair	*env_pair_from_str(char const *str)
{
	t_pair	*new_pair;

	new_pair = (t_pair *)ft_calloc(1, sizeof(t_pair));
	new_pair->key = ft_strcdup(str, '=');
	if (ft_strcmp(new_pair->key, str) == '\0')
		new_pair->value = NULL;
	else
	{
		while (*str != '=')
			str++;
		new_pair->value = ft_strcdup(++str, '\0');
	}
	return (new_pair);
}

int	env_compare_pairs(t_list *elem_cmp, t_list *temp_elem)
{
	t_pair	*data_pair;
	t_pair	*elem_pair;

	data_pair = (t_pair *)elem_cmp->data;
	elem_pair = (t_pair *)temp_elem->data;
	return (ft_strcmp(data_pair->key, elem_pair->key) < 0);
}

t_pair	*env_get_pair(t_env *env, char const *key)
{
	t_list	*lst;
	t_pair	*pair;

	lst = env->collection;
	while (lst != NULL)
	{	
		if (env_get_value_from_key(lst->data, key) == 0)
		{
			pair = lst->data;
			return (lst->data);
		}
		lst = lst->next;
	}
	return (NULL);
}
