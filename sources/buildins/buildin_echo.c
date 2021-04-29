#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static int	check_arg_n(char *str)
{
	if (ft_strcmp(str, "-") == 0)
		return (0);
	if (str[0] != '-')
		return (0);
	str++;
	while (*str)
		if (*str++ != 'n')
			return (0);
	return (1);
}

static void	print_n(char *str)
{
	if (!check_arg_n(str))
		ft_putstr_fd("\n", 1);
}

int	buildin_echo(char **argv, t_minishell *shell)
{
	int	arg_n;
	int	temp;
	int	i;

	i = 0;
	arg_n = 1;
	shell = NULL;
	if (argv[1] != 0)
	{
		while (argv[++i] != 0)
		{
			temp = check_arg_n(argv[i]);
			if (temp == 0 || (temp && arg_n == 0))
			{
				arg_n = 0;
				ft_putstr_fd(argv[i], 1);
				if (argv[i + 1] != 0)
					ft_putstr_fd(" ", 1);
			}
		}
		print_n(argv[1]);
	}
	else
		ft_putstr_fd("\n", 1);
	return (0);
}
