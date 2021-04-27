/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:14:31 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 13:02:19 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"

int	factory_init(t_factory *factory, t_minishell *shell)
{
	char *env_path;
	
	env_path = env_get_value(shell->env, "PATH");
	if (env_path != NULL)
		factory->paths = ft_split(env_path, ':'); // не проверяю на ошибку
	else
		factory->paths = NULL;
	factory->commands = NULL;
	factory->result = 1;
	return (1);
}

int	factory_run_line(t_list *words, t_minishell *shell)
{
	t_pword		*word;
	t_factory	factory;

	if (!factory_init(&factory, shell))
		return (0);
	if (factory_build_commands(&factory, words, shell))
	{
		// ft_list_foreach((t_list *)factory.commands, command_print);
		factory_exec_commands(&factory, shell);
	}
	factory_destroy(&factory);
	return (factory.result);
}

int	factory_destroy(t_factory *factory)
{
	if (factory->paths != NULL)
		free_array(factory->paths);
	ft_dlist_free(&factory->commands, command_list_destroy);
	return (1);
}
