/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_squotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:02:44 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 15:21:41 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "errors.h"

int	pstate_squotes(char **line, struct s_pcontext *context)
{
	if (!pbuffer_open(context, EWT_WORD))
		return (0);
	while (21)
	{
		if (**line == '\0')
			return (pcontext_error(context, err_print(_ERR_MULTL, 1, 258)));
		else if (**line == '\'')
		{
			(*line)++;
			return (pcontext_return_state(context));
		}
		else
		{
			if (!pbuffer_add_char(context, **line))
				return (0);
			(*line)++;
		}
	}
}
