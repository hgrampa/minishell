/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:35:48 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 19:37:45 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int				pcontext_set_state(struct s_pcontext *context, t_state_body next_state)
{
	ft_stack_push(&context->state_stack, context->current_state);
	context->current_state = next_state;
	return (1);
}

int				pcontext_return_state(struct s_pcontext *context)
{
	context->current_state = (t_state_body)ft_stack_pop(&context->state_stack);
	return (1);
}

t_state_body	pcontext_previous_state(struct s_pcontext *context)
{
	return ((t_state_body)ft_stack_peek(context->state_stack));
}

int				pcontext_end_process(struct s_pcontext *context, int status)
{
	context->process = 0;
	return(status);
}
