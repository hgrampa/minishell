#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"
#include "minishell.h"

static int	continue_ta (int result, t_pair *e_pair, t_pair *n_pair, t_env *env)
{
	if (n_pair->value == NULL && e_pair)
		result = 1;
	if (result == 0)
	{
		if (e_pair == NULL)
		{
			ft_list_add(&(env->collection), n_pair);
			env_update(env);
		}
		else
		{
			free(e_pair->value);
			e_pair->value = ft_strdup(n_pair->value);
			env_update(env);
			result = 1;
		}
	}
	if (result != 0)
	{
		env_free_pair(n_pair);
		free(n_pair);
	}
	return (result);
}

static int	error_option(char c)
{
	ft_putstr_fd("minishell: export: -", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("export: usage: export [-nf] ", 2);
	ft_putstr_fd("[name[=value] ...] or export -p\n", 2);
	return (-1);
}

static int	error_invalid(char *str)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("' : not a valid identifier\n", 2);
	return (-1);
}

static int	treat_arg(t_env	*env, char const *arg_str)
{
	t_pair	*new_pair;
	t_pair	*exist_pair;
	int		result;
	int		plus;
	char	*test;

	result = 0;
	new_pair = env_pair_from_str(arg_str);
	plus = check_for_plus(new_pair->key);
	exist_pair = env_get_pair(env, new_pair->key);
	if (new_pair && plus && exist_pair && exist_pair->value)
	{
		test = ft_strdup(new_pair->value);
		free(new_pair->value);
		new_pair->value = ft_concat2(exist_pair->value, test);
		free(test);
	}
	if (new_pair->key[0] == '-')
		result = error_option(new_pair->key[1]);
	else if (check_invalid_key(new_pair->key))
		result = error_invalid(new_pair->key);
	return (continue_ta(result, exist_pair, new_pair, env));
}

int	buildin_export(char **argv, t_minishell *shell)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	if (argv[1] == 0)
		print_export_list(shell->env->collection);
	else
	{
		while (argv[i] != 0 && result != -1)
			result = treat_arg(shell->env, argv[i++]);
	}
	return (result != 0);
}
