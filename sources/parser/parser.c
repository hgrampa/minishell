/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 13:04:19 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/14 20:39:26 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"



void			pcontext_set_state(struct s_pcontext *context, t_state_body next_state)
{
	context->current_state = next_state;
	ft_stack_push(&context->state_stack, next_state);
}

void			pcontext_return_state(struct s_pcontext *context)
{
	context->current_state = ft_stack_pop(context->state_stack);
}

t_state_body	*pcontext_previous_state(struct s_pcontext *context)
{
	return ((t_state_body *)ft_stack_peek(context->state_stack));
}

void			pcontext_end_process(struct s_pcontext *context)
{
	context->process = 0;
}

int		esc_state(char **line, t_list **words, struct s_pcontext *context)
{
	// *line++; промотка этого символа очень вариативна 
	while (21)
	{
		
		if (**line == '\0')
		{
			pcontext_end_process(context);
			return (1); // TODO или сразу тут ошибку сделать
		}
	}
}

int		env_state(char **line, t_list **words, struct s_pcontext *context)
{
	// *line++; промотка этого символа очень вариативна 
	// (иногда он часть слова и иногда нет)
	// открываю буфер (локальный) (так что бы ему было пофиг если уже открыт)
	while (21)
	{
		//	проверка следуещего за $ символа - может ли он начинать имя
		//		если не подошел проверяю останется ли он и этот первый символ
		//	промотка до символа не являющегося частью имени (в т.ч. $)
		//	{ 
		// 		добавление имени в локальный буфер 
		//	}
		// 	получение значения по имени (строка, пустая строка, NULL)
		// 	?возврат значения переменной или формирование слов/а на месте
		// 
	}
}

int		squotes_state(char **line, t_list **words, struct s_pcontext *context)
{
	*line++;
	// открываю буфер (так что бы ему было пофиг если уже открыт)
	while (21)
	{
		if (**line == '\0')
		{
			pcontext_end_process(context);
			return (1); // TODO или сразу тут ошибку сделать
		}
		else if (line == '\'')
		{
			// ! не закрываю буфер
			pcontext_return_state(context);
			return (1);
		}
		// добавляю символ к буферу
		*line++;
	}
}

int		wquotes_state(char **line, t_list **words, struct s_pcontext *context)
{
	*line++;
	// открываю буфер
	while (21)
	{
		if (**line == '\0')
		{
			pcontext_end_process(context);
			return (1); // TODO или сразу тут ошибку сделать
		}
		else if (line == '\"')
		{
			// ! не закрываю буфер
			pcontext_return_state(context);
			return (1);
		}
		else if (**line == '$')
		{
			pcontext_set_state(context, env_state);
			return (1);
		}
		else if (**line == '\\')
		{
			pcontext_set_state(context, squotes_state);
			return (1);
		}
		// добавляю символ к буферу
		*line++;
	}	
}

int		core_state(char **line, t_list **words, struct s_pcontext *context)
{
	while (21)
	{
		if (**line == '\0')
		{
			pcontext_end_process(context);
			return (1); // TODO вероятно можно что-то лучше придумать
		}
		else if (**line == '$')
		{
			pcontext_set_state(context, env_state);
			return (1);
		}
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
		else if (**line == '\\')
		{
			pcontext_set_state(context, esc_state);
			return (1);
		}
		else if (ft_strchr(_PRS_CONTROLERS, **line) != NULL)
		{
			// закрываю буфер и записываю слово
			// добавляю симол к новому слову
			// ! если это что то вроде >> - должно остаться одним словом
			// Вероятно я добавлю еще одну state
		}
		else if (ft_strchr(_PRS_DELIMITERS, **line) != NULL)
		{
			// закрываю буфер и записываю слово
			// проматываю символ
		}
		// добавляю символ к буферу
		*line++;
	}
	return (1);
}

int		parse_line(char *line, t_list **words)
{
	int					result;
	struct s_pcontext	context;

	pcontext_set_state(&context, core_state);
	context.buffer = NULL;
	context.process = 1;

	while (context.process)
	{
		result = context.current_state(&line, words, &context);
		if (result = 0)
			break ;
	}
	// if (context.current_state != core_state)
		// ошибка либо кавычки не закрыты или еще че
	ft_stack_free(&context.state_stack, NULL); // ? по идее тут не должно что=то быть (разве что при ошибке)
	free(context.buffer);
	return (result);
}
