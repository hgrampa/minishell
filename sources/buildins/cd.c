#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "environment.h"

char	*dash_case(char *str, t_pair *old_pwd_pair)
{
	if (ft_strncmp (str, "-", 2) == 0)
	{
		if (old_pwd_pair == NULL || old_pwd_pair->value == NULL)
		{
			printf("bash: cd: OLDPWD not set\n");
			return (NULL);
		}
		else
			return (old_pwd_pair->value);
	}
	else
		return (str);
}

int	ft_cd (char *str, t_env *env)
{
	char	cwd[100];
	int		result;
	t_pair	*pwd_pair;
	t_pair	*old_pwd_pair;

	pwd_pair = env_get_pair(env, "PWD");
	old_pwd_pair = env_get_pair(env, "OLDPWD");
	str = dash_case(str, old_pwd_pair);
	if (str == NULL)
		return (-1);
	if (pwd_pair == NULL && old_pwd_pair == NULL)
		result = 0;
	else if (pwd_pair == NULL)
		old_pwd_pair->value = ft_strdup("");
	else if (pwd_pair == NULL)
	{
		free(old_pwd_pair->value);
		old_pwd_pair->value = ft_strdup(getcwd(cwd, 100));
	}
	else if (old_pwd_pair != NULL)
	{
		free(old_pwd_pair->value);
		old_pwd_pair->value = ft_strdup(pwd_pair->value);
	}
	printf("old pwd %s\n", getcwd(cwd, 100));
	result = chdir(str);
	if (result != -1 && pwd_pair != NULL)
		env_set(env, "PWD", getcwd(cwd, 100));
	printf("new pwd %s\n", getcwd(cwd, 100));
	return (result);
}

int	buildin_cd(char **argv, t_minishell *shell)
{
	int	result;

	if (argv[1] == 0)
		result = 0;
	if (argv[2] == 0)
		result = ft_cd(argv[1], shell->env);
	else
		result = -1;
	return (result); //TODO errror management to be done
}

// int	main(int ac, char **av, char const **env)
// {
// 	int		result;
// 	t_minishell *shell;

// 	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
// 	shell->env = env_create(env);
// 	// env_unset(shell->env, "PWD");
// 	//env_unset(shell->env, "OLDPWD");
// 	// env_set(shell->env, "OLDPWD", NULL);
// 	result = buildin_cd(av, shell);
// 	printf("result = %d\n", result);
// 	printf("________LISTS________\n");
// 	print_list(shell->env->collection);
// 	env_destroy(shell->env);
// 	free(shell);
// 	return (result);
// }
