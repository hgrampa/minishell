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
	if (argv[1] == 0)
		exit(0);
	else
	{
		if (!check_digit(argv[1]))
		{
			printf("bash: exit: %s: numeric argument required\n", argv[1]);
			errno = 255;
			exit(255);
		}
		if (argv[2] == 0)
		{
			errno = ft_atoi(argv[1]) % 255;
			printf("exit %d\n", errno);
			exit(errno);
		}			
		else
			printf("bash: exit: too many arguments\n");
	}	
	//printf("did'n't exit\n");
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
