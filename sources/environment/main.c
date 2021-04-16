
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 12:04:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/11 12:04:05 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/libft.h"
# include "../../includes/environment.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int main(int ac, char **av, char const **env)
{
	t_env *environment;
	
	printf("%d\n", ac);
	printf("%s\n", av[0]);
	environment = env_create(env);
	env_set(environment, "A", NULL);
	env_set(environment, "AA", "");
	env_set(environment, "HOME2", "test1321321321321321321321321321");
	env_set(environment, "REAL_USER", "meow");
	env_unset(environment, "A");
	env_unset(environment, "MYSTIC_SHIT");
	env_unset(environment, "__CF_USER_TEXT_ENCODING");
	printf("________REPRESENT________\n");
	print_represent(environment->represent);
	printf("________LISTS________\n");
	print_list(environment->collection);
	env_destroy(environment);
	// t_pair *pair = create_pair_from_str("test");
	// printf("key %s\n", pair->key);
	// printf("value %s\n\n", pair->value);

	// pair = create_pair_from_str("test=");
	// printf("key %s\n", pair->key);
	// printf("value %s\n\n", pair->value);

	// pair = create_pair_from_str("test=test");
	// printf("key %s\n", pair->key);
	// printf("value %s\n\n", pair->value);

	return (1);
}