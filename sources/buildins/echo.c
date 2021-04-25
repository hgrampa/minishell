#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static void	print_n(char *str)
{
	if (ft_strncmp(str, "-n", 3) != 0)
		printf("\n");
}

int	buildin_echo(char **argv, t_minishell *shell)
{
	int	arg_n;
	int	temp;
	int	i;

	i = 0;
	arg_n = 1;
	if (argv[1] != 0)
	{
		while (argv[++i] != 0)
		{
			temp = (ft_strncmp(argv[i], "-n", 3) == 0);
			if (temp == 0 || (temp && arg_n == 0))
			{
				arg_n = 0;
				printf("%s", argv[i]);
				if (argv[i + 1] != 0)
					printf(" ");
			}
		}
		print_n(argv[1]);
	}
	else
		printf("\n");
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_minishell	*shell;

// 	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
// 	buildin_echo(av, shell);
// 	free(shell);
// }
