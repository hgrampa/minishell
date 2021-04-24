/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_cntr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:16:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 12:48:44 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "errors.h"

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
		return (pcontext_end_process(context, err_print(_ERR_UNKNOWN, 0)));
	if (!pbuffer_close(context)	|| !pbuffer_open(context, type)
		|| !pbuffer_close(context))
		return (0);
	if (type == EWT_REDIRECT3) 	// проматываю line
		(*line) += 2;
	else
		(*line)++;
	return(pcontext_return_state(context));
}
