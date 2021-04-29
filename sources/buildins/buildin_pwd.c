#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "errno.h"
#include "minishell.h"

int	buildin_pwd(char **argv, t_minishell *shell)
{
	char	*result;

	result = (char *)malloc(100);
	result = getcwd(result, 100);
	shell = NULL;
	if (argv[1] != 0)
	{
		if (argv[1][0] == '-')
		{
			ft_putstr_fd("minishell: pwd: -", 2);
			ft_putstr_fd(&argv[1][1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			free(result);
			return (1);
		}
		else
			ft_putstr_fd(result, 1);
	}
	else
		ft_putstr_fd(result, 1);
	ft_putstr_fd("\n", 1);
	free(result);
	return (0);
}
