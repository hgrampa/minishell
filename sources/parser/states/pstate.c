/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:35:48 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 14:13:23 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void			pcontext_set_state(struct s_pcontext *context, t_state_body next_state)
{
	ft_stack_push(&context->state_stack, context->current_state);
	context->current_state = next_state;
}

void			pcontext_return_state(struct s_pcontext *context)
{
	context->current_state = (t_state_body)ft_stack_pop(&context->state_stack);
}

t_state_body	*pcontext_previous_state(struct s_pcontext *context)
{
	return ((t_state_body *)ft_stack_peek(context->state_stack));
}

void			pcontext_end_process(struct s_pcontext *context)
{
	context->process = 0;
}
