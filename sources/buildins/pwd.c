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
	if (argv[1] != 0)
	{
		if (argv[1][0] == '-')
		{
			printf("bash: pwd: -%c: invalid option\n", argv[1][1]);
			errno = 1;
		}
		else
			printf("%s\n", result);
	}
	else
		printf("%s\n", result);
	free(result);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_minishell *shell;

// 	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
// 	buildin_pwd(av, shell);
// 	free(shell);
// 	return (0);
// }
