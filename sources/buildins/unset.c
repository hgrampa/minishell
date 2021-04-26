#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"
#include "minishell.h"

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
		result = -1;
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

int	buildin_unset(char **argv, t_minishell *shell)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	if (argv[1] != 0)
	{
		while (argv[i] != 0 && result != -1)
			result = treat_arg(shell->env, argv[i++]);
	}
	return (result == -1);
}

// int	main(int ac, char **av, char const **env)
// {
// 	t_minishell *shell;

// 	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
// 	shell->env = env_create(env);
// 	env_set(shell->env, "A", NULL);
// 	buildin_unset(av, shell);
// 	printf("________LISTS________\n");
// 	print_list(shell->env->collection);
// 	env_destroy(shell->env);
// 	free(shell);
// 	return (0);
// }
