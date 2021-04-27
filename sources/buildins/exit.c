#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "errno.h"
#include "minishell.h"

static int	check_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}

int	buildin_exit(char **argv, t_minishell *shell)
{
	shell = NULL;
	if (argv[1] == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else
	{
		if (!check_digit(argv[1]))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		if (argv[2] == 0)
		{
			errno = ft_atoi(argv[1]) % 255;
			ft_putstr_fd("exit\n", 1);
			exit(errno);
		}			
		else
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
	}
	return (1);
}

// int	main(int ac, char **av)
// {
// 	t_minishell *shell;

// 	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
// 	printf("%d\n", buildin_exit(av, shell));
// 	free(shell);
// 	return (0);
// }
