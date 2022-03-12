/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:00:48 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:47:02 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"

int	factory_is_redirection(enum e_pword_type type)
{
	return (type == EWT_REDIR_IN || type == EWT_REDIR_OUT
		|| type == EWT_REDIR_APPEND);
}

int	factory_build_commands(t_factory *factory, t_list *words)
{
	int						result;
	struct s_build_context	context;

	context.process = 1;
	while (context.process)
	{
		context.argl = NULL;
		context.command = NULL;
		result = factory_biuld_command(factory, &words, &context);
		if (result == 0)
		{
			ft_list_free(&context.argl, NULL);
			if (context.command != NULL)
				command_destroy(context.command);
			return (0);
		}
		if (context.command == NULL)
			continue ;
		context.command->argv = ft_list_tosa(context.argl);
		if (context.argl != NULL)
			ft_list_free(&context.argl, NULL);
		ft_dlist_add(&factory->commands, context.command);
	}
	return (1);
}
