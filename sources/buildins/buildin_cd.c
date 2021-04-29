#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "environment.h"

static char	*dash_case(char *str, t_pair *old_pwd_pair)
{
	if (ft_strncmp (str, "-", 2) == 0)
	{
		if (old_pwd_pair == NULL || old_pwd_pair->value == NULL)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		else
		{
			printf("%s\n", old_pwd_pair->value);
			return (old_pwd_pair->value);
		}
	}
	else
		return (str);
}

static char	*set_pwd(t_pair *pwd_pair)
{
	if (pwd_pair)
		return (pwd_pair->value);
	else
		return ("");
}

static int	ft_cd (char *str, t_env *env)
{
	char	cwd[100];
	int		result;
	t_pair	*pwd_pair;
	t_pair	*old_pwd_pair;

	pwd_pair = env_get_pair(env, "PWD");
	old_pwd_pair = env_get_pair(env, "OLDPWD");
	str = dash_case(str, old_pwd_pair);
	if (str == NULL)
		return (1);
	result = chdir(str);
	if (result != -1 && old_pwd_pair != NULL)
	{
		if (old_pwd_pair->value[0] == '\0')
			env_set(env, "OLDPWD", getcwd(cwd, 100));
		else
			env_set(env, "OLDPWD", set_pwd(pwd_pair));
	}
	if (result != -1 && pwd_pair != NULL)
		env_set(env, "PWD", getcwd(cwd, 100));
	return (result);
}

int	buildin_cd(char **argv, t_minishell *shell)
{
	int		result;
	t_pair	*home_pair;

	if (argv[1] == 0)
	{
		home_pair = env_get_pair(shell->env, "HOME");
		if (home_pair == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		else
			result = ft_cd(home_pair->value, shell->env);
	}
	else
		result = ft_cd(argv[1], shell->env);
	if (result == -1)
		err_cd_print(NULL, 1, 1, argv[1]);
	return (result == -1);
}
