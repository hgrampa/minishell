/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pword.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 13:56:44 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/20 14:05:07 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PWORD_H
# define PWORD_H

# include <unistd.h>
# include <stdio.h>
# include "libft.h"

enum e_pword_type
{
	EWT_UNKNOWN = -1,
	EWT_WORD,
	EWT_PIPE,
	EWT_SEMICOLON,
	EWT_REDIRECT1, // < TODO norm delete comment
	EWT_REDIRECT2, // >
	EWT_REDIRECT3, // >>
};

typedef struct s_pword
{
	char				*value;
	enum e_pword_type	type;
}				t_pword;

t_pword	*pword_new(char *value, enum e_pword_type type);
void	pword_destroy(void *data);
void	pword_print(void *data);

#endif
