#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "errno.h"

static int	check_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str++))
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		printf("exit\n");
		exit(0);
	}
	else
	{
		if (!check_digit(av[1]))
		{
			printf("bash: exit: %s: numeric argument required\n", av[1]);
			errno = 255;
			exit(255);
		}
		if (ac == 2)
		{
			printf("exit\n");
			errno = ft_atoi(av[1]) % 255;
			exit(errno);
		}			
		else
			printf("bash: exit: too many arguments\n");
	}	
	//printf("did'n't exit\n");
	return (0);
}
