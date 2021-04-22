/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:17:02 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 17:29:37 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

# define _PRS_ESC_CORE_CAHRS "\"\';|><$ \t"
# define _PRS_ESC_WQUOTES_CAHRS "\"\'$"

// Эта стаддия пока замороженна
// TODO проверить экранирование пробела в ""
// TODO проверить самоэкранирование
int		pstate_esc(char **line, struct s_pcontext *context)
{
	// char *ancor;

	(*line)++;
	if (**line == '\0') // В теории можно избавиться от якоря
	{
		pcontext_end_process(context);
		return (0); // TODO возврат ошибки (что мультистрочный ввод не поддерживается)
	}
	if (pcontext_previous_state() == pstate_core)
	{
		if (ft_strchr(_PRS_ESC_CORE_CAHRS, **line) != NULL)
		{
			pbuffer_add_char(context, **line);
			(*line)++;
		}
		else
		{
			// ЧТо там в главной стадии не помню
		}
	}
	else
	{
		if (ft_strchr(_PRS_ESC_WQUOTES_CAHRS, **line) != NULL)
		{
			pbuffer_add_char(context, **line);
			(*line)++;
		}
		else
		{
			pbuffer_add_char(context, "\");
			pbuffer_add_char(context, **line);
			(*line)++;
		}
	}
	pcontext_return_state(context);
	return (1);
}
