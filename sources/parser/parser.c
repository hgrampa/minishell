/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 13:04:19 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/15 23:18:17 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void			pcontext_set_state(struct s_pcontext *context, t_state_body next_state)
{
	ft_stack_push(&context->state_stack, context->current_state);
	context->current_state = next_state;
}

void			pcontext_return_state(struct s_pcontext *context)
{
	context->current_state = (t_state_body)ft_stack_pop(&context->state_stack);
}

t_state_body	*pcontext_previous_state(struct s_pcontext *context)
{
	return ((t_state_body *)ft_stack_peek(context->state_stack));
}

void			pcontext_end_process(struct s_pcontext *context)
{
	context->process = 0;
}

int		env_isname_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

// Эта стаддия пока замороженна
int		esc_state(char **line, t_list **words, struct s_pcontext *context)
{
	// (*line)++; промотка этого символа очень вариативна 
	// while (21)
	// {
		
	// 	if (**line == '\0')
	// 	{
	// 		pcontext_end_process(context);
	// 		return (1); // TODO или сразу тут ошибку сделать
	// 	}
	// }
	return (1);
}

int		env_wq_state(char **line, t_list **words, struct s_pcontext *context)
{

}

int		env_cr_state(char **line, t_list **words, struct s_pcontext *context)
{

}

int		env_state(char **line, t_list **words, struct s_pcontext *context)
{
	// (*line)++; промотка этого символа очень вариативна
	// 
	// открываю буфер (локальный)

	char *anchor;
	anchor = *line;
	(*anchor)++;
	//	проверка следуещего за $ символа - УС ли он
	if (ft_strchr(_PRS_CONTROLERS, *anchor) != NULL)
	{
		// $ добавляется к слову 
		// линия проматывается
		// стадия закрывается
	}
	else if (ft_strchr(_PRS_QUOTES, *anchor) != NULL)
	{
		if (pcontext_previous_state == wquotes_state)
		{
			// $ добавляется к слову 
			// линия проматывается
			// стадия закрывается
		}
		else
		{
			// линия проматывается до anchor
			// стадия закрывается
		}
	}
	//	проверка следуещего за $ символа - может ли он начинать имя (главное чтоб не цифра)
	if (env_isname_char(*anchor) && !ft_isdigit(*anchor))
	{
		*line = anchor;
		// работаем
		while (21)
		{
			if (**line == '\0')
			{
				// имкенно возвращаемя на предыдущую стадию
				// 	эта не знает что делать с концом строки
				pcontext_return_state(context);
				// но не ошибка
				return (1); 
			}
			else if (env_isname_char(**line))
			{
				// добавление имени в локальный буфер
				// (*line)++;
			}
			else
			{
				// получение значения по имени (строка, пустая строка, NULL)
				// ? формирование слов/а на месте в зависимости от прошлой стадии
			}
		}
	}
	else
	{
		// anchor++;
		// линия проматывается до anchor
		// стадия закрывается
	}
}

int		squotes_state(char **line, t_list **words, struct s_pcontext *context)
{
	(*line)++;
	pbuffer_open(context); // открываю буфер (так что бы ему было пофиг если уже открыт)
	while (21)
	{
		if (**line == '\0')
		{
			pcontext_end_process(context);
			return (0); // TODO или сразу тут ошибку сделать
		}
		else if (**line == '\'')
		{
			pcontext_return_state(context);
			(*line)++;
			return (1);
		}
		else
		{
			// добавляю символ к буферу
			pbuffer_add_char(context, **line);
			(*line)++;
		}
	}
}

int		wquotes_state(char **line, t_list **words, struct s_pcontext *context)
{
	(*line)++;
	pbuffer_open(context);
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
		// else if (**line == '$')
		// {
		// 	pcontext_set_state(context, env_state);
		// 	return (1);
		// }
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

int		core_state(char **line, t_list **words, struct s_pcontext *context)
{
	while (21)
	{
		if (**line == '\0')
		{
			pbuffer_close(context);
			pcontext_end_process(context);
			return (1); // TODO вероятно можно что-то лучше придумать
		}
		// else if (**line == '$')
		// {
		// 	pcontext_set_state(context, env_state);
		// 	return (1);
		// }
		else if (**line == '\"')
		{
			pcontext_set_state(context, wquotes_state);
			return (1);
		}
		else if (**line == '\'')
		{
			pcontext_set_state(context, squotes_state);
			return (1);
		}
		// else if (**line == '\\')
		// {
		// 	pcontext_set_state(context, esc_state);
		// 	return (1);
		// }
		// else if (ft_strchr(_PRS_CONTROLERS, **line) != NULL)
		// {
		// 	pcontext_set_state(context, cntrl_state);
		// 	return(1);
		// 	// закрываю буфер и записываю слово
		// 	// добавляю симол к новому слову
		// 	// ! если это что то вроде >> - должно остаться одним словом
		// 	// Вероятно я добавлю еще одну state
		// }
		else if (ft_strchr(_PRS_DELIMITERS, **line) != NULL)
		{
			pbuffer_close(context);
			(*line)++;
		}
		else
		{
			// добавляю символ к буферу (открывая его)
			pbuffer_add_char(context, **line);
			(*line)++;
		}
	}
	return (1);
}

int		parse_line(char *line, t_list **words)
{
	int					result;
	struct s_pcontext	context;

	pcontext_set_state(&context, core_state);
	context.buffer = NULL;
	context.words = NULL;
	context.process = 1;
	while (context.process)
	{
		result = context.current_state(&line, words, &context);
		if (result == 0)
			break ;
	}
	// if (context.current_state != core_state)
		// ошибка либо кавычки не закрыты или еще че
	ft_stack_free(&context.state_stack, NULL); // ? по идее тут не должно что=то быть (разве что при ошибке)
	if (context.buffer != NULL)
		free(context.buffer);
	*words = context.words;
	return (result);
}




