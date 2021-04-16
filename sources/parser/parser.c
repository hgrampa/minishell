/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 13:04:19 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 13:48:36 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "environment.h"

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

int		squotes_state(char **line, t_list **words, struct s_pcontext *context)
{
	(*line)++;
	pbuffer_open(context, EWT_WORD); // открываю буфер (так что бы ему было пофиг если уже открыт)
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
	pbuffer_open(context, EWT_WORD);
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
		else if (**line == '$')
		{
			pcontext_set_state(context, env_state);
			return (1);
		}
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
		// else if (**line == '\\')
		// {
		// 	pcontext_set_state(context, esc_state);
		// 	return (1);
		// }
		else if (ft_strchr(_PRS_CONTROLERS, **line) != NULL)
		{
			pcontext_set_state(context, cntrl_state);
			return(1);
			// закрываю буфер и записываю слово
			// добавляю симол к новому слову
			// ! если это что то вроде >> - должно остаться одним словом
			// Вероятно я добавлю еще одну state
		}
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

int		parse_line(t_env *env, char *line, t_list **words)
{
	int					result;
	struct s_pcontext	context;

	pcontext_set_state(&context, core_state);
	context.buffer = NULL;
	context.words = NULL;
	context.process = 1;
	context.env = env;
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
