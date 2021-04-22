/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:17:02 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 19:39:00 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int		pstate_esc(char **line, struct s_pcontext *context)
{
	pbuffer_open(context, EWT_WORD);
	(*line)++;
	if (**line == '\0')
		return (pcontext_end_process(context, 0)); // TODO возврат ошибки (что мультистрочный ввод не поддерживается)
	if (pcontext_previous_state(context) == pstate_wquotes
		&& ft_strchr(_PRS_ESC_WQUOTES_CAHRS, **line) == NULL)
			pbuffer_add_char(context, '\\');
	pbuffer_add_char(context, **line);
	(*line)++;
	return (pcontext_return_state(context));
}
