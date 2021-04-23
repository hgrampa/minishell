/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/23 12:52:25 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"

char	*create_key_value_str(t_pair *pair)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = (char *)ft_calloc(1, (ft_strlen(pair->key)
				+ ft_strlen(pair->value) + 2) * sizeof(char));
	while (pair->key[i] != '\0')
		new_str[j++] = pair->key[i++];
	new_str[j++] = '=';
	i = 0;
	while (pair->value[i] != '\0')
		new_str[j++] = pair->value[i++];
	new_str[j++] = '\0';
	return (new_str);
}

static int	check_null_value(t_pair *pair)
{
	return (pair->value == NULL);
}

int	create_represent(t_env *environment, int ln)
{
	t_list	*lst;
	char	**represent;
	char	*new_str;
	int		i;

	i = 0;
	represent = (char **)ft_calloc(1, (ln + 1) * sizeof(char *));
	if (represent == NULL)
		return (0);
	lst = environment->collection;
	while (lst != NULL)
	{	
		if (!check_null_value(lst->data))
		{
			new_str = create_key_value_str(lst->data);
			represent[i++] = new_str;
		}
		lst = lst->next;
	}
	represent[i] = NULL;
	free_array(environment->represent);
	free(environment->represent);
	environment->represent = represent;
	return (1);
}

t_pair	*pair_from_str(char const *str)
{
	t_pair	*new_pair;

	new_pair = (t_pair *)ft_calloc(1, sizeof(t_pair));
	new_pair->key = ft_strcdup(str, '=');
	if (ft_strncmp(new_pair->key, str, 30) == '\0')
		new_pair->value = NULL;
	else
	{
		while (*str != '=')
			str++;
		new_pair->value = ft_strcdup(++str, '\0');
	}
	return (new_pair);
}

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
				pair_from_str(represent[i])))
			return (NULL);
	}
	ft_list_sort(environment->collection);
	create_represent(environment, ft_list_count(environment->collection) + 1); // TODO защитить
	return (environment);
}
