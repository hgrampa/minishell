/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 13:04:19 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 12:22:38 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "environment.h"

static void	parse_context_init(struct s_pcontext *context, t_env *env)
{
	context->current_state = pstate_core;
	context->state_stack = NULL;
	context->buffer = NULL;
	context->words = NULL;
	context->process = 1;
	context->env = env;
}

int	parse_line(t_env *env, char *line, t_list **words)
{
	int					result;
	struct s_pcontext	context;

	parse_context_init(&context, env);
	while (context.process)
	{
		result = context.current_state(&line, &context);
		if (result == 0)
			break ;
	}
	ft_stack_free(&(context.state_stack), NULL);
	if (context.buffer != NULL)
		sbuffer_destroy(context.buffer);
	if (result == 1)
		*words = context.words;
	return (result);
}
