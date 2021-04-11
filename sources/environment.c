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

# include "../includes/libft.h"
# include "environment.h"
# include <stdio.h>

/*
**	Creates an instance of t_env based on a string
**
**		- String of key value pair divided by sign '\n' in such format:
**			KEY_1=VALUE_1
**			KEY_2=VALUE_2
**		- In case of failure - returns NULL
*/


t_pair *create_pair(char const *str)
{
	t_pair new_pair;
	t_pair *new_pair_ptr;

	new_pair.key = ft_strcdup(str, '=');
	//printf("key = |%s|\n", new_pair->key);
	while (*str != '=')
		str++;
	new_pair.value = ft_strcdup(++str, '\0');
	new_pair_ptr = (t_pair*)ft_calloc(1, sizeof(t_pair));
	*new_pair_ptr = new_pair;
	//printf("value = |%s|\n", new_pair->value);
	return(new_pair_ptr);
}

t_env	*env_create(char const *represent[])
{
	t_env *environment;
	int i;

	i = -1;
	environment = (t_env*)ft_calloc(1, sizeof(t_env));
	while(represent[++i] != NULL)
	{
		if (!ft_list_add(&(environment->collection), create_pair(represent[i])))
		{
			printf("ERROR\n");
			break ;
		}
	}
	return (environment);
}
