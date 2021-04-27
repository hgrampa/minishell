/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbuffer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:35:44 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 10:59:34 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "errors.h"

int	pbuffer_add_char(struct s_pcontext *context, char c)
{
	if (context->buffer == NULL)
	{
		if (!pbuffer_open(context, EWT_WORD))
			return (0);
	}
	return (sbuffer_add_char(context->buffer, c));
}

int	pbuffer_add_str(struct s_pcontext *context, char *str)
{
	if (context->buffer == NULL)
	{
		if (!pbuffer_open(context, EWT_WORD))
			return (0);
	}
	return (sbuffer_add_str(context->buffer, str));
}

int	pbuffer_open(struct s_pcontext *context, enum e_pword_type type)
{
	if (context->buffer == NULL)
	{
		context->buffer = sbuffer_create(_PRS_BUFFSIZE);
		if (context->buffer == NULL)
			return (err_print(NULL, 0, 1));
		context->buffer_type = type;
	}
	return (1);
}

int	pbuffer_close(struct s_pcontext *context)
{
	t_pword	*word;

	if (context->buffer != NULL)
	{
		word = (t_pword *)ft_calloc(1, sizeof(t_pword));
		if (word == NULL)
			return (err_print(NULL, 0, 1));
		word->type = context->buffer_type;
		word->value = ft_strdup(context->buffer->str);
		if (!ft_list_add(&context->words, word))
		{
			free(word->value);
			free(word);
			sbuffer_destroy(context->buffer);
			return (err_print(NULL, 0, 1));
		}
		sbuffer_destroy(context->buffer);
		context->buffer = NULL;
	}
	return (1);
}
