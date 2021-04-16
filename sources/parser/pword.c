/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pword.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 12:37:21 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/15 12:40:41 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

char *pword_unpack(t_pword **word);

t_pword	*pword_new(char *value, enum e_pword_type type)
{
	t_pword *new;

	new = (t_pword *)ft_calloc(1, sizeof(t_pword));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->type = type;
	return (new);
}
