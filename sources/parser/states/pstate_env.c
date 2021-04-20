/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pstate_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 13:16:05 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/20 12:08:43 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "environment.h"

static int	env_isname_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int			pstate_env(char **line, struct s_pcontext *context)
{
	char *anchor;
	anchor = *line;
	anchor++;
	//	проверка следуещего за $ символа - УС ли он
	if (ft_strchr(_PRS_CONTROLERS, *anchor) != NULL)
	{
		// $ добавляется к слову 
		pbuffer_add_char(context, **line);
		// линия проматывается до anchor (символ после $)
		*line = anchor;
		// стадия закрывается
		pcontext_return_state(context);
		return (1);
	}
	else if (ft_strchr(_PRS_QUOTES, *anchor) != NULL) // TODO можно только на ' проверять
	{
		if (pcontext_previous_state(context) == pstate_wquotes)
		{
			// $ добавляется к слову 
			pbuffer_add_char(context, **line);
			// линия проматывается до anchor (символ после $)
			*line = anchor;
			// стадия закрывается
			pcontext_return_state(context);
			return (1);
		}
		else
		{
			*line = anchor;
			// стадия закрывается
			pcontext_return_state(context);
			return (1);
		}
	}
	//	проверка следуещего за $ символа - может ли он начинать имя (главное чтоб не цифра)
	if (env_isname_char(*anchor) && !ft_isdigit(*anchor))
	{
		*line = anchor;
		// работаем
		int	len;
		char *name;
		char *value;
		
		len = 0;
		while (21)
		{
			if (env_isname_char(**line))
			{
				len++; // вычисляю длинну имени
				(*line)++;
			}
			else
			{
				// дублирую имя по его длине
				name = ft_strndup(anchor, len);
				// получение значения по имени (строка, пустая строка, NULL)
				value = env_get_value(context->env, name);
				// value = ft_strdup("A B  C   D");
				if (value != NULL)
				{
					// формирование слов/а на месте в зависимости от прошлой стадии
					if (pcontext_previous_state(context) == pstate_wquotes)
						pbuffer_add_str(context, value);
					else
					{
						while (*value != '\0' )
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
				free(name);
				pcontext_return_state(context);
				return (1);
			}
		}
	}
	else
	{
		anchor++;
		// линия проматывается до anchor (символ после после $)
		*line = anchor;
		// стадия закрывается
		pcontext_return_state(context);
		return (1);
	}
}
