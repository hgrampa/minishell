/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 13:04:19 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 15:12:15 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "environment.h"
#include "factory.h"

static void	parse_context_init(struct s_pcontext *context, t_env *env,
	t_list **words)
{
	if (*words != NULL)
	{
		ft_list_free(words, pword_destroy);
		*words = NULL;
	}
	context->current_state = pstate_core;
	context->state_stack = NULL;
	context->buffer = NULL;
	context->words = NULL;
	context->process = 1;
	context->error = 0;
	context->env = env;
}

int	parse_line(t_minishell *shell, char *line, t_list **words)
{
	int					result;
	struct s_pcontext	context;

	while (*line != '\0')
	{
		parse_context_init(&context, shell->env, words);
		while (context.process)
		{
			result = context.current_state(&line, &context);
			if (result == 0)
				break ;
		}
		ft_stack_free(&(context.state_stack), NULL);
		if (context.buffer != NULL)
			sbuffer_destroy(context.buffer);
		*words = context.words;
		if (result == 1 && !context.error)
			result = factory_run_line(shell->factory, *words, shell);
		if (!result)
			break ;
	}
	return (result);
}
