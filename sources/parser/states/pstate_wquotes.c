/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_wquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:02:13 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 19:40:09 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	pstate_wquotes(char **line, struct s_pcontext *context)
{
	pbuffer_open(context, EWT_WORD);
	while (21)
	{
		if (**line == '\0')
			return (pcontext_end_process(context, 0));
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
			pbuffer_add_char(context, **line);
			(*line)++;
		}
	}	
}
