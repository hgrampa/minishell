#include <stdio.h>
#include "libft.h"

static void	print_n(char *str)
{
	if (ft_strncmp(str, "-n", 3) != 0)
		printf("\n");
}

int	main(int ac, char **av)
{
	int	arg_n;
	int	temp;
	int	i;

	i = 0;
	arg_n = 1;
	if (ac > 1)
	{
		while (++i != ac)
		{
			temp = (ft_strncmp(av[i], "-n", 3) == 0);
			if (temp == 0 || (temp && arg_n == 0))
			{
				arg_n = 0;
				printf("%s", av[i]);
				if (i + 1 != ac)
					printf(" ");
			}
		}
		print_n(av[1]);
	}
	else
		printf("\n");
	return (0);
}
