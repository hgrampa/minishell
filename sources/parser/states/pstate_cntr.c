/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_cntr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:16:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 14:08:20 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "errors.h"

static enum e_pword_type	cntrl_get_type(char *line)
{
	if (ft_strncmp(line, "|", 1) == 0)
		return (EWT_PIPE);
	else if (ft_strncmp(line, ";", 1) == 0)
		return (EWT_SEMICOLON);
	else if (ft_strncmp(line, "<", 1) == 0)
		return (EWT_REDIR_IN);
	else if (ft_strncmp(line, ">>", 2) == 0)
		return (EWT_REDIR_APPEND);
	else if (ft_strncmp(line, ">", 1) == 0)
		return (EWT_REDIR_OUT);
	else
		return (EWT_UNKNOWN);
}

static int	cntrl_add_value(enum e_pword_type type, struct s_pcontext *context)
{
	if (type == EWT_PIPE)
		return (pbuffer_add_str(context, "|"));
	else if (type == EWT_SEMICOLON)
		return (pbuffer_add_str(context, ";"));
	else if (type == EWT_REDIR_IN)
		return (pbuffer_add_str(context, "<"));
	else if (type == EWT_REDIR_APPEND)
		return (pbuffer_add_str(context, ">>"));
	else if (type == EWT_REDIR_OUT)
		return (pbuffer_add_str(context, ">"));
	return (1);
}

int	pstate_cntrl(char **line, struct s_pcontext *context)
{
	enum e_pword_type	type;

	type = cntrl_get_type(*line);
	if (type == EWT_UNKNOWN)
		return (pcontext_end_process(context, err_print(_ERR_UNKNOWN, 0, 1)));
	if (!pbuffer_close(context) || !pbuffer_open(context, type)
		|| !cntrl_add_value(type, context) || !pbuffer_close(context))
		return (0);
	if (type == EWT_REDIR_APPEND)
		(*line) += 2;
	else
		(*line)++;
	if (type == EWT_SEMICOLON)
		return (pcontext_end_process(context, 1));
	return (pcontext_return_state(context));
}
