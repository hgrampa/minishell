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
		printf("declare -x %s", pair->key);
		if (pair->value != NULL)
			printf("=\"%s\"", pair->value);
		printf("\n");
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

static int	treat_arg(t_env	*env, char const *arg_str)
{
	t_pair	*new_pair;
	int		result;

	result = 0;
	new_pair = pair_from_str(arg_str);
	if (new_pair->key[0] == '-')
	{
		printf("bash: export: -%c: invalid option\n", new_pair->key[1]);
		printf("export: usage: export [-nf] [name[=value] ...] or export -p\n");
		result = -1;
	}
	else if (check_invalid_key(new_pair->key))
		result = printf("bash: export: '%s' : not a valid identifier\n",
				new_pair->key);
	if (result == 0)
	{
		if (!ft_list_add(&(env->collection), new_pair) | !env_update(env))
			result = 0;
	}
	else
	{
		free_pair(new_pair);
		free(new_pair);
	}
	return (result);
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
	return (result == -1);
}

// int	main(int ac, char **av, char const **env)
// {
// 	t_minishell *shell;

// 	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
// 	shell->env = env_create(env);
// 	env_set(shell->env, "A", NULL);
// 	printf("%d\n", buildin_export(av, shell));
// 	printf("________LISTS________\n");
// 	print_list(shell->env->collection);
// 	env_destroy(shell->env);
// 	free(shell);
// 	return (0);
// }
