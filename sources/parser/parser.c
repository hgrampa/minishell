/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 13:04:19 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/11 15:20:54 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

enum e_parser_st
{
	PRS_MAIN,
	partial_quoting,
	full_quoting,
};

int		core_state(char **line, t_list **words);
int		strong_quotes_state(char **line, t_list **words);
int		weak_quotes_state(char **line, t_list **words);
int		env_state(char **line, t_list **words);

int		parse_line(char **line, t_list **words)
{
	
	if (!ft_list_add(words, ft_strdup("dfsdfsdf")))
	{
		return (0);
	}

	return (1);
}
