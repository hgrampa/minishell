#include <stdio.h>
#include "../../includes/libft.h"

int	main(int ac, char **av)
{
	int	arg_n;
	int	i;

	i = 1;
	if (ac == 1)
	{
		printf("\n");
		return (0);
	}
	arg_n = (ft_strncmp(av[i], "-n", 3) == 0);
	i += arg_n;
	while (i != ac)
	{
		printf("%s", av[i++]);
		if (i != ac)
			printf(" ");
	}	
	if (!arg_n)
		printf("\n");
	return (0);
}
