#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "errno.h"
#include "minishell.h"

static int	check_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' && !(ft_isdigit(str[i])))
		return (0);
	i++;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i++]) || i > 18 )
			return (0);
	}
	return (1);
}

int	buildin_exit(char **argv, t_minishell *shell)
{
	int	exit_code;

	if (argv[1] == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else
	{
		if (!check_digit(argv[1]))
		{
			ft_putstr_fd("exit\n", 1);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			minishell_exit(shell, 255);
		}
		if (argv[2] == 0)
		{
			exit_code = ft_atoi(argv[1]) % 255;
			ft_putstr_fd("exit\n", 1);
			minishell_exit(shell, exit_code);
		}			
		else
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	return (1);
}
