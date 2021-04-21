#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "environment.h"

char *dash_case(char *str,t_pair *old_pwd_pair)
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

int	main(int ac, char **av, char const **env)
{
	int		result;
	t_env	*environment;

	printf("%s\n", av[0]);
	result = 0;
	environment = env_create(env);
	//env_unset(environment, "PWD");
	//env_unset(environment, "OLDPWD");
	// env_set(environment, "OLDPWD", NULL);
	if (ac == 2)
		result = ft_cd(av[1], environment);
	else if (ac > 2)
		result = -1;
	printf("result = %d\n", result);
	// printf("________LISTS________\n");
	// print_list(environment->collection);
	env_destroy(environment);
	return (result);
}
