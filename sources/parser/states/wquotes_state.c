/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wquotes_state.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:02:13 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 14:03:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	wquotes_state(char **line, t_list **words, struct s_pcontext *context)
{
	(*line)++;
	pbuffer_open(context, EWT_WORD);
	while (21)
	{
		if (**line == '\0')
		{
			pcontext_end_process(context);
			return (0); // TODO или сразу тут ошибку сделать
		}
		else if (**line == '\"')
		{
			pcontext_return_state(context);
			(*line)++;
			return (1);
		}
		else if (**line == '$')
		{
			pcontext_set_state(context, env_state);
			return (1);
		}
		// else if (**line == '\\')
		// {
		// 	pcontext_set_state(context, squotes_state);
		// 	return (1);
		// }
		else
		{
			// добавляю символ к буферу
			pbuffer_add_char(context, **line);
			(*line)++;
		}
	}	
}
