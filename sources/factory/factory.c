/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:14:31 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/28 18:19:57 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"
#include "minishell.h"

t_factory	*factory_create(void)
{
	t_factory	*factory;

	factory = (t_factory *)ft_calloc(1, sizeof(t_factory));
	if (!factory)
		return (NULL);
	return (factory);
}

static int	factory_init_build(t_factory *factory, t_minishell *shell)
{
	char	*env_path;

	env_path = env_get_value(shell->env, "PATH");
	if (env_path != NULL)
		factory->paths = ft_split(env_path, ':');
	else
		factory->paths = NULL;
	factory->commands = NULL;
	factory->result = 1;
	return (1);
}

int	factory_run_line(t_factory *factory, t_list *words, t_minishell *shell)
{
	factory_init_build(factory, shell);
	if (factory_build_commands(factory, words))
		factory_exec_commands(factory, shell);
	factory_clear(factory);
	return (factory->result);
}

int	factory_clear(t_factory *factory)
{
	if (factory->paths != NULL)
		free_array(factory->paths);
	factory->paths = NULL;
	ft_dlist_free(&factory->commands, command_list_destroy);
	factory->commands = NULL;
	return (1);
}

int	factory_destroy(t_factory *factory)
{
	factory_clear(factory);
	free(factory);
	return (1);
}
