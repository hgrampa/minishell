#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"
#include "minishell.h"

static int	unset_check_invalid_key(char *key)
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

static int	error_option(char c)
{
	ft_putstr_fd("minishell: unset: -", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(": invalid option\n", 2);
	ft_putstr_fd("unset: usage: unset [-f] [-v] [name ...]\n", 2);
	return (-1);
}

static int	treat_arg(t_env	*env, char const *arg_str)
{
	int		result;
	char	*str;

	result = 0;
	str = (char *)arg_str;
	if (str[0] == '-')
		result = error_option(str[1]);
	else if (unset_check_invalid_key(str))
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("' : not a valid identifier\n", 2);
		result = -1;
	}
	if (result == 0)
	{
		if (!env_unset(env, str))
			result = 0;
	}
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
