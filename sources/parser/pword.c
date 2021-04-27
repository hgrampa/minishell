/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pword.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 12:37:21 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/20 14:00:55 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pword.h"

t_pword	*pword_new(char *value, enum e_pword_type type)
{
	t_pword	*new;

	new = (t_pword *)ft_calloc(1, sizeof(t_pword));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->type = type;
	return (new);
}

void	pword_destroy(void *data)
{
	t_pword	*word;

	word = (t_pword *)data;
	free(word->value);
	free(word);
}

void	pword_print(void *data)
{
	t_pword	*word;

	word = (t_pword *)data;
	printf(">> type: %d, val: \"%s\"\n", word->type, word->value);
}
