/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_cntr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:16:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 21:11:25 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static enum e_pword_type	cntrl_get_type(char *line)
{
	if (ft_strncmp(line, "|", 1))
		return (EWT_PIPE);
	else if (ft_strncmp(line, ";", 1))
		return (EWT_SEMICOLON);
	else if (ft_strncmp(line, "<", 1))
		return (EWT_REDIRECT1);
	else if (ft_strncmp(line, ">>", 2))
		return (EWT_REDIRECT3);
	else if (ft_strncmp(line, ">", 1))
		return (EWT_REDIRECT2);
	else
		return (EWT_UNKNOWN);
}

int							pstate_cntrl(char **line, struct s_pcontext *context)
{
	enum e_pword_type	type;
	
	type = cntrl_get_type(*line);
	if (type == EWT_UNKNOWN)
		return (pcontext_end_process(context, 0));
	pbuffer_close(context); // закрываю буфер и записываю слово
	pbuffer_open(context, type);  	// открываю буфер добавляю строку(может NULL) и тип симол к новому слову
	pbuffer_close(context); // закрываю буфер и записываю слово
	if (type == EWT_REDIRECT3) 	// проматываю line
		(*line) += 2;
	else
		(*line)++;
	return(pcontext_return_state(context));
}
