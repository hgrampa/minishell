#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"

int	check_invalid_key(char *key)
{
	if (ft_isdigit(key[0]))
		return (1);
	while (*key)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (1);
		key++;
	}
	return (0);
}

int	treat_arg(t_env	*env, char const *arg_str)
{
	t_pair	*new_pair;
	int		result;

	result = 0;
	new_pair = pair_from_str(arg_str);
	if (new_pair->key[0] == '-')
	{
		result = printf("bash: unset: -%c: invalid option\n", new_pair->key[1]);
		printf("unset: usage: unset [-f] [-v] [name ...]\n");
	}
	else if (check_invalid_key(new_pair->key))
		result = printf("bash: unset: '%s' : not a valid identifier\n",
				new_pair->key);
	if (result == 0)
	{
		if (!env_unset(env, arg_str))
			result = 0;
	}
	free_pair(new_pair);
	free(new_pair);
	return (result);
}

int	main(int ac, char **av, char const **env)
{
	t_env	*environment;
	int		i;

	i = 1;
	environment = env_create(env);
	//env_set(environment, "A", NULL);
	if (ac > 1)
	{
		while (i != ac)
			treat_arg(environment, av[i++]);
	}
	// printf("________LISTS________\n");
	// print_list(environment->collection);
	env_destroy(environment);
	return (0);
}
