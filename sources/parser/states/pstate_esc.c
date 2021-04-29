/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:17:02 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 15:21:46 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "errors.h"

int	pstate_esc(char **line, struct s_pcontext *context)
{
	if (!pbuffer_open(context, EWT_WORD))
		return (0);
	(*line)++;
	if (**line == '\0')
		return (pcontext_error(context, err_print(_ERR_MULTL, 1, 258)));
	if (pcontext_previous_state(context) == pstate_wquotes
		&& ft_strchr(_PRS_ESC_WQUOTES_CAHRS, **line) == NULL)
	{
		if (!pbuffer_add_char(context, '\\'))
			return (0);
	}
	if (!pbuffer_add_char(context, **line))
		return (0);
	(*line)++;
	return (pcontext_return_state(context));
}
