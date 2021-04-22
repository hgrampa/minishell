/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbuffer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:35:44 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 21:12:16 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	pbuffer_add_char(struct s_pcontext *context, char c)
{
	if (context->buffer == NULL)
	{
		if (!pbuffer_open(context, EWT_WORD))
			return (0); // TODO возврат ошибки
	}
	// len = ft_strlen(context->buffer);
	// size = (len + 1) * sizeof(char);
	// tmp = (char *)ft_realloc(context->buffer, size, size + (1 * sizeof(char)));
	// if (tmp == NULL)
	// 	return (0);
	// tmp[len] = c;
	// tmp[len + 1] = '\0';
	// context->buffer = tmp;
	return (sbuffer_add_char(context->buffer, c));
}

int	pbuffer_add_str(struct s_pcontext *context, char *str)
{
	if (context->buffer == NULL)
	{
		if (!pbuffer_open(context, EWT_WORD))
			return (0); // TODO возврат ошибки
	}
	// tmp = ft_concat2(context->buffer, str);
	// if (tmp == NULL)
	// 	return (0);
	// free(context->buffer);
	// context->buffer = tmp;
	return (sbuffer_add_str(context->buffer, str));
}

int	pbuffer_open(struct s_pcontext *context, enum e_pword_type type)
{
	if (context->buffer == NULL)
	{
		context->buffer = sbuffer_create(_PRS_BUFFSIZE);
		if (context->buffer == NULL)
			return (0); // TODO возврат ошибки
		context->buffer_type = type;
		// // tmp = ft_strdup("");
		// tmp = (char *)ft_calloc(1, sizeof(char));
		// if (tmp == NULL)
		// 	return (0);
		// context->buffer = tmp;
	}
	return (1);
}

int	pbuffer_close(struct s_pcontext *context)
{
	t_pword	*word;

	if (context->buffer != NULL)
	{
		word = (t_pword *)ft_calloc(1, sizeof(t_pword));
		if (word == NULL) // TODO возврат ошибки
			return (0);
		word->type = context->buffer_type;
		word->value = ft_strdup(context->buffer->str);
		if (!ft_list_add(&context->words, word))
		{
			free(word->value);
			free(word);
			sbuffer_destroy(context->buffer);
			return (0);
		}
		sbuffer_destroy(context->buffer);
		context->buffer = NULL;
	}
	return (1);
}
