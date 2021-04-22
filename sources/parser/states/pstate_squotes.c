/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_squotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:02:44 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 19:39:24 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	pstate_squotes(char **line, struct s_pcontext *context)
{
	pbuffer_open(context, EWT_WORD); // открываю буфер (так что бы ему было пофиг если уже открыт)
	while (21)
	{
		if (**line == '\0')
			return (pcontext_end_process(context, 0)); // TODO возврат ошибки
		else if (**line == '\'')
		{
			(*line)++;
			return (pcontext_return_state(context));
		}
		else
		{
			// добавляю символ к буферу
			pbuffer_add_char(context, **line);
			(*line)++;
		}
	}
}
