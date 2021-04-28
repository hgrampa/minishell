/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/27 13:13:59 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "environment.h"

void	print_represent(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_putstr_fd(array[i++], 1);
		ft_putstr_fd("\n", 1);
	}
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

void	increment_shlvl(t_env *env)
{
	t_pair	*shlvl_pair;
	int		level;

	shlvl_pair = env_get_pair(env, "SHLVL");
	if (shlvl_pair != NULL)
	{
		level = ft_atoi(shlvl_pair->value);
		level++;
		free(shlvl_pair->value);
		if (level == 1000)
			shlvl_pair->value = ft_strdup("");
		else if (level == 1001)
			shlvl_pair->value = ft_strdup("1");
		else
			shlvl_pair->value = ft_itoa(level);
	}
}