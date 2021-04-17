#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"

int	main(int ac, char **av, char const **env)
{
	t_env	*environment;

	environment = env_create(env);
	if (ac == 1)
		print_represent(environment->represent);
	else
		printf("out of subject %s\n", av[1]); // TODO return errno
	env_destroy(environment);
	return (0);
}
