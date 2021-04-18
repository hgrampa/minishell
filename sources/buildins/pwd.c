#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "errno.h"

int	main(int ac, char **av)
{
	char	*result;

	result = (char *)malloc(100);
	result = getcwd(result, 100);
	if (ac > 1)
	{
		if (av[1][0] == '-')
		{
			printf("bash: pwd: -%c: invalid option\n", av[1][1]);
			errno = 1;
		}
		else
		{
			printf("%s\n", result);
			free(result);
		}
	}
	else
	{
		printf("%s\n", result);
		free(result);
	}
	return (0);
}
