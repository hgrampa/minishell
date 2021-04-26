#include <stdio.h>
#include "libft.h"
#include "minishell.h"

static int	check_arg_n(char *str)
{
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
			temp = check_arg_n(argv[i]);
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
