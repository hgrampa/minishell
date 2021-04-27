/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:03:49 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 12:45:01 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	pstate_core(char **line, struct s_pcontext *context)
{
	while (21)
	{
		if (**line == '\0')
		{
			if (!pbuffer_close(context))
				return (0);
			return (pcontext_end_process(context, 1));
		}
		else if (**line == '$')
			return (pcontext_set_state(context, pstate_env));
		else if (**line == '\"')
		{
			(*line)++;
			return (pcontext_set_state(context, pstate_wquotes));
		}
		else if (**line == '\'')
		{
			(*line)++;
			return (pcontext_set_state(context, pstate_squotes));
		}
		else if (**line == '\\')
			return (pcontext_set_state(context, pstate_esc));
		else if (ft_strchr(_PRS_CONTROLERS, **line) != NULL)
			return (pcontext_set_state(context, pstate_cntrl));
		else if (ft_strchr(_PRS_DELIMITERS, **line) != NULL)
		{
			if (!pbuffer_close(context))
				return (0);
			(*line)++;
		}
		else
		{
			if (!pbuffer_add_char(context, **line))
				return (0);
			(*line)++;
		}
	}
	return (1); // TODO norm 25 lines 
}
