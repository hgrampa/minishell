#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"

int	main(int ac, char **av, char const **env)
{
	t_env	*environment;
	t_pair	*path_pair;

	environment = env_create(env);
	//env_unset(environment, "PATH");
	if (ac == 1)
	{
		path_pair = env_get_pair(environment, "PATH");
		if (path_pair == NULL)
			printf("bash: env: No such file or directory\n");
		else
			print_represent(environment->represent);
	}	
	else
		printf("out of subject : %s\n", av[1]); // TODO return errno
	env_destroy(environment);
	return (0);
}
