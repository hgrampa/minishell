/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:35:48 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:35:26 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "errors.h"

int	pcontext_set_state(struct s_pcontext *context,
	t_state_body next_state)
{
	if (!ft_stack_push(&context->state_stack, context->current_state))
		return (err_print(NULL, 0, 1));
	context->current_state = next_state;
	return (1);
}

int	pcontext_return_state(struct s_pcontext *context)
{
	context->current_state = (t_state_body)ft_stack_pop(&context->state_stack);
	return (1);
}

t_state_body	pcontext_previous_state(struct s_pcontext *context)
{
	return ((t_state_body)ft_stack_peek(context->state_stack));
}

int	pcontext_end_process(struct s_pcontext *context, int status)
{
	context->process = 0;
	return (status);
}

int	pcontext_error(struct s_pcontext *context, int status)
{
	context->error = 1;
	return (pcontext_end_process(context, status));
}
