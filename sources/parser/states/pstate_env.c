/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:16:05 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 14:08:40 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "environment.h"
#include "errors.h"

static char	*get_var_name(char **line)
{
	char	*name;
	char	*anchor;
	int		len;

	anchor = *line;
	len = 0;
	while (env_isname_char(**line))
	{
		len++;
		(*line)++;
	}
	name = ft_strndup(anchor, len);
	if (name == NULL)
		return (NULL);
	return (name);
}

static int	pstate_set_value(struct s_pcontext *context, char *name)
{
	char	*value;

	value = env_get_value(context->env, name);
	if (value == NULL)
		return (1);
	if (pcontext_previous_state(context) == pstate_wquotes)
		pbuffer_add_str(context, value);
	else
	{
		while (*value != '\0')
		{
			if (ft_strchr(_PRS_DELIMITERS, *value) != NULL)
			{
				if (!pbuffer_close(context))
					return (0);
			}
			else
			{
				if (!pbuffer_add_char(context, *value))
					return (0);
			}
			value++;
		}
	}
	return (1);
}

static int	pstate_rename_var(char **line, struct s_pcontext *context)
{
	char	*name;

	if (env_isname_char(**line) && !ft_isdigit(**line))
	{
		name = get_var_name(line);
		if (name == NULL)
			return (pcontext_end_process(context, err_print(NULL, 0, 1)));
		if (!pstate_set_value(context, name))
		{
			free(name);
			return (0);
		}
		free(name);
		return (pcontext_return_state(context));
	}
	else if (**line == '?')
	{
		if (!pstate_set_value(context, "?"))
			return (0);
	}
	(*line)++;
	return (pcontext_return_state(context));
}

static int	pstate_env_to_anchor_exit(char	*anchor, char **line,
	struct s_pcontext *context)
{
	*line = anchor;
	return (pcontext_return_state(context));
}

int	pstate_env(char **line, struct s_pcontext *context)
{
	char	*anchor;

	anchor = *(line) + 1;
	if (*anchor == '\0' || ft_strchr(_PRS_DELIMITERS, *anchor) != NULL
		|| ft_strchr(_PRS_CONTROLERS, *anchor) != NULL)
	{
		if (!pbuffer_add_char(context, **line))
			return (0);
		*line = anchor;
		return (pcontext_return_state(context));
	}
	else if (ft_strchr(_PRS_QUOTES, *anchor) != NULL)
	{
		if (pcontext_previous_state(context) == pstate_wquotes)
		{
			if (!pbuffer_add_char(context, **line))
				return (0);
			pstate_env_to_anchor_exit(anchor, line, context);
		}
		else
			pstate_env_to_anchor_exit(anchor, line, context);
	}
	(*line)++;
	return (pstate_rename_var(line, context));
}
