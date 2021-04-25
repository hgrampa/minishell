/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_wquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:02:13 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 12:48:44 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "errors.h"

int	pstate_wquotes(char **line, struct s_pcontext *context)
{
	if (!pbuffer_open(context, EWT_WORD))
		return (0);
	while (21)
	{
		if (**line == '\0')
			return (pcontext_end_process(context, err_print(_ERR_MULTL, 1)));
		else if (**line == '\"')
		{
			(*line)++;
			return (pcontext_return_state(context));
		}
		else if (**line == '$')
			return (pcontext_set_state(context, pstate_env));
		else if (**line == '\\')
			return (pcontext_set_state(context, pstate_esc));
		else
		{
			if (!pbuffer_add_char(context, **line))
				return (0);
			(*line)++;
		}
	}	
}
