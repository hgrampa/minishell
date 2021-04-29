#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"
#include "minishell.h"

int	buildin_env(char **argv, t_minishell *shell)
{
	t_pair	*path_pair;
	int		result;

	result = 0;
	if (argv[1] == 0)
	{
		path_pair = env_get_pair(shell->env, "PATH");
		if (path_pair == NULL)
		{
			ft_putstr_fd("minishell: env: No such file or directory\n", 2);
			result = 1;
		}
		else
			env_print_represent(shell->env->represent);
	}	
	else
	{
		ft_putstr_fd("out of subject\n", 2);
		result = 1;
	}
	return (result);
}
