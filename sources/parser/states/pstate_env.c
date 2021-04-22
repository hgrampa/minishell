/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:16:05 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 21:03:46 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "environment.h"

static int	env_isname_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*get_var_name(char **line)
{
	char	*name;
	char	*anchor;
	int		len;

	anchor = *line;
	len = 0;
	while (env_isname_char(**line))
	{
		len++; // вычисляю длинну имени
		(*line)++;
	}
	name = ft_strndup(anchor, len);
	if (name == NULL)
		return (NULL);
	return (name);
}

static void	pstate_set_value(struct s_pcontext *context, char *name)
{
	char *value;

	value = env_get_value(context->env, name); // получение значения по имени (строка, пустая строка, NULL)
	if (value != NULL)
	{
		if (pcontext_previous_state(context) == pstate_wquotes) // формирование слов/а на месте в зависимости от прошлой стадии
			pbuffer_add_str(context, value);
		else
		{
			while (*value != '\0')
			{
				if (ft_strchr(_PRS_DELIMITERS, *value) != NULL)
				{
					pbuffer_close(context);
					value++;
				}
				else
				{
					pbuffer_add_char(context, *value);
					value++;
				}
			}
		}
	}
}

static int	pstate_rename_var(char **line, struct s_pcontext *context) // TODO Придумать понятное имя функции
{
	char *name;

	if (env_isname_char(**line) && !ft_isdigit(**line)) //	проверка следуещего за $ символа - может ли он начинать имя (главное чтоб не цифра)
	{
		name = get_var_name(line);
		if (name == NULL)
			return (pcontext_end_process(context, 0)); // TODO Возврат ошибки
		pstate_set_value(context, name);
		free(name); // TODO можно переделать get_var_name чтоб без малока было
		return (pcontext_return_state(context));
	}
	(*line)++; // линия проматывается до anchor (символ после после $)
	return (pcontext_return_state(context)); // стадия закрывается
}

// !!! TODO $ без имени
// TODO "$ foo"
int			pstate_env(char **line, struct s_pcontext *context)
{
	char *anchor;

	anchor = *(line) + 1;
	if (*anchor == '\0' || ft_strchr(_PRS_DELIMITERS, *anchor) != NULL 
		|| ft_strchr(_PRS_CONTROLERS, *anchor) != NULL)
	{
		pbuffer_add_char(context, **line); // $ добавляется к слову 
		*line = anchor; // линия проматывается до anchor (символ после $)
		return (pcontext_return_state(context));
	}
	else if (ft_strchr(_PRS_QUOTES, *anchor) != NULL) // TODO можно только на ' проверять
	{
		if (pcontext_previous_state(context) == pstate_wquotes)
		{
			pbuffer_add_char(context, **line); // $ добавляется к слову 
			*line = anchor; // линия проматывается до anchor (символ после $)
			return (pcontext_return_state(context)); // стадия закрывается
		}
		else
		{
			*line = anchor;
			return (pcontext_return_state(context)); // стадия закрывается
		}
	}
	(*line)++;
	return (pstate_rename_var(line, context));
}

