#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"
#include "minishell.h"

static void	print_export_list(t_list *collection)
{
	t_pair	*pair;
	t_list	*tmp;

	tmp = collection;
	while (tmp != NULL)
	{
		pair = tmp->data;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(pair->key, 1);
		if (pair->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(pair->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		tmp = tmp->next;
	}
}

static int	check_invalid_key(char *key)
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

static int	check_for_plus(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i + 1] != '\0')
		i++;
	if (str[i] != '+')
		return (0);
	str[i] = '\0';
	return (1);
}

static int	continue_ta (int result, t_pair *e_pair, t_pair *n_pair, t_env *env)
{
	if (result == 0)
	{
		if (e_pair == NULL)
		{
			if (!ft_list_add(&(env->collection), n_pair) || !env_update(env))
				result = 1;
		}
		else
		{
			free(e_pair->value);
			e_pair->value = ft_strdup(n_pair->value);
			result = 21;
		}
	}
	if (result != 0)
	{
		free_pair(n_pair);
		free(n_pair);
	}
	return (result);
}

static int	error_option(char c)
{
	ft_putstr_fd("bash: export: -", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("export: usage: export [-nf] ", 2);
	ft_putstr_fd("[name[=value] ...] or export -p\n", 2);
	return (-1);
}

static int	error_invalid(char *str)
{
	ft_putstr_fd("bash: export: '", 2);
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
	new_pair = pair_from_str(arg_str);
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

// int	main(int ac, char **av, char const **env)
// {
// 	t_minishell	*shell;

// 	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
// 	shell->env = env_create(env);
// 	env_set(shell->env, "A", NULL);
// 	printf("%d\n", buildin_export(av, shell));
// 	// printf("________LISTS________\n");
// 	// print_list(shell->env->collection);
// 	env_destroy(shell->env);
// 	free(shell);
// 	return (0);
// }
