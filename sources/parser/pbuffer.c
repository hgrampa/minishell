/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbuffer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 11:35:44 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 16:01:34 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

int	pbuffer_add_char(struct s_pcontext *context, char c)
{
	char	*tmp;
	size_t	len;
	size_t	size;

	if (context->buffer == NULL)
	{
		if (!pbuffer_open(context, EWT_WORD))
			return (0);
	}
	len = ft_strlen(context->buffer);
	size = (len + 1) * sizeof(char);
	tmp = (char *)ft_realloc(context->buffer, size, size + (1 * sizeof(char)));
	if (tmp == NULL)
		return (0);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	
	context->buffer = tmp;
	return (1);
}

int	pbuffer_add_str(struct s_pcontext *context, char *str)
{
	char *tmp;
	
	if (context->buffer == NULL)
	{
		if (!pbuffer_open(context, EWT_WORD))
			return (0);
	}
	tmp = ft_concat2(context->buffer, str);
	if (tmp == NULL)
		return (0);
	free(context->buffer);
	context->buffer = tmp;
	return (1);
}

int	pbuffer_open(struct s_pcontext *context, enum e_pword_type type)
{
	char *tmp;

	if (context->buffer == NULL)
	{
		// tmp = ft_strdup("");
		tmp = (char *)ft_calloc(1, sizeof(char));
		if (tmp == NULL)
			return (0);
		context->buffer = tmp;
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
		word->type = context->buffer_type;
		word->value = ft_strdup(context->buffer);
		if (!ft_list_add(&context->words, word))
			return (0);
		free(context->buffer);
		context->buffer = NULL;
	}
	return (1);
}
