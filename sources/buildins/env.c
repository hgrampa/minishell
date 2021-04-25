#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"
#include "minishell.h"

int	buildin_env(char **argv, t_minishell *shell)
{
	t_pair	*path_pair;

	if (argv[1] == 0)
	{
		path_pair = env_get_pair(shell->env, "PATH");
		if (path_pair == NULL)
			printf("bash: env: No such file or directory\n");
		else
			print_represent(shell->env->represent);
	}	
	else
		printf("out of subject\n"); // TODO return errno
}

// int	main(int ac, char **av, char const **env)
// {
// 	t_minishell *shell;

// 	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
// 	shell->env = env_create(env);
// 	env_unset(shell->env, "PATH");
// 	buildin_env(av, shell);
// 	env_destroy(shell->env);
// 	free(shell);
// 	return (0);
// }
