/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   esc_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:17:02 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 16:01:45 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// Эта стаддия пока замороженна
int		esc_state(char **line, t_list **words, struct s_pcontext *context)
{
	// (*line)++; промотка этого символа очень вариативна 
	// while (21)
	// {
		
	// 	if (**line == '\0')
	// 	{
	// 		pcontext_end_process(context);
	// 		return (0);
	// 	}
	// }
	return (1);
}
