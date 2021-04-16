/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squotes_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:02:44 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 14:03:10 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	squotes_state(char **line, t_list **words, struct s_pcontext *context)
{
	(*line)++;
	pbuffer_open(context, EWT_WORD); // открываю буфер (так что бы ему было пофиг если уже открыт)
	while (21)
	{
		if (**line == '\0')
		{
			pcontext_end_process(context);
			return (0); // TODO или сразу тут ошибку сделать
		}
		else if (**line == '\'')
		{
			pcontext_return_state(context);
			(*line)++;
			return (1);
		}
		else
		{
			// добавляю символ к буферу
			pbuffer_add_char(context, **line);
			(*line)++;
		}
	}
}
