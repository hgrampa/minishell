/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_represent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/28 17:50:32 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "environment.h"

static int	check_null_value(t_pair *pair)
{
	return (pair->value == NULL);
}

int	env_create_represent(t_env *environment, int ln)
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
			new_str = env_create_key_value_str(lst->data);
			represent[i++] = new_str;
		}
		lst = lst->next;
	}
	represent[i] = NULL;
	free_array(environment->represent);
	environment->represent = represent;
	return (1);
}

void	env_print_represent(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_putstr_fd(array[i++], 1);
		ft_putstr_fd("\n", 1);
	}
}

void	env_print_list(t_list *lst)
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

char	*env_create_key_value_str(t_pair *pair)
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
