/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_core.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:03:49 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 18:52:20 by hgrampa          ###   ########.fr       */
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
			pbuffer_close(context);
			pcontext_end_process(context);
			return (1);
		}
		else if (**line == '$')
		{
			pcontext_set_state(context, pstate_env);
			return (1);
		}
		else if (**line == '\"')
		{
			(*line)++;
			pcontext_set_state(context, pstate_wquotes);
			return (1);
		}
		else if (**line == '\'')
		{
			(*line)++;
			pcontext_set_state(context, pstate_squotes);
			return (1);
		}
		else if (**line == '\\')
		{
			pcontext_set_state(context, pstate_esc);
			return (1);
		}
		else if (ft_strchr(_PRS_CONTROLERS, **line) != NULL)
		{
			pcontext_set_state(context, pstate_cntrl);
			return(1);
		}
		else if (ft_strchr(_PRS_DELIMITERS, **line) != NULL)
		{
			pbuffer_close(context);
			(*line)++;
		}
		else
		{
			// добавляю символ к буферу (открывая его)
			pbuffer_add_char(context, **line);
			(*line)++;
		}
	}
	return (1);
}
