/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:03:49 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 14:08:27 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static int	pstate_core_enter_state(t_state_body state, char **line,
	struct s_pcontext *context)
{
	(*line)++;
	return (pcontext_set_state(context, state));
}

static int	pstate_core_exit(struct s_pcontext *context)
{
	if (!pbuffer_close(context))
		return (0);
	return (pcontext_end_process(context, 1));
}

int	pstate_core(char **line, struct s_pcontext *context)
{
	while (21)
	{
		if (**line == '\0')
			return (pstate_core_exit(context));
		else if (**line == '$')
			return (pcontext_set_state(context, pstate_env));
		else if (**line == '\"')
			return (pstate_core_enter_state(pstate_wquotes, line, context));
		else if (**line == '\'')
			return (pstate_core_enter_state(pstate_squotes, line, context));
		else if (**line == '\\')
			return (pcontext_set_state(context, pstate_esc));
		else if (ft_strchr(_PRS_CONTROLERS, **line) != NULL)
			return (pcontext_set_state(context, pstate_cntrl));
		else if (ft_strchr(_PRS_DELIMITERS, **line) != NULL)
		{
			if (!pbuffer_close(context))
				return (0);
		}
		else if (!pbuffer_add_char(context, **line))
			return (0);
		(*line)++;
	}
}
