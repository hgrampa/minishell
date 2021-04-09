/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nwrd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:26:52 by hgrampa           #+#    #+#             */
/*   Updated: 2021/02/21 18:00:19 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Returns a duplicate of the next *word in a string
**
**		str - moves to the first character after the word
**
** 		in case of no words - allocate an empty string
**		in case of an error - return NULL (str return to origin)
**
** 		"word" - any sequence of characters separated by: {' ', '\t'}
*/

char	*ft_gnwrd(char **str)
{
	int		i;
	int		word_len;
	char	*next_word;
	char	*anchor;

	anchor = *str;
	while (**str == ' ' || **str == '\t')
		(*str)++;
	word_len = 0;
	while (**str != ' ' && **str != '\t' && **str != '\0')
	{
		(*str)++;
		word_len++;
	}
	if (!(next_word = (char*)ft_calloc(word_len + 1, sizeof(char))))
	{
		*str = anchor;
		return (NULL);
	}
	i = 0;
	*str -= word_len;
	while (i < word_len)
		next_word[i++] = *(*str)++;
	next_word[i] = '\0';
	return (next_word);
}

/*
**	Returns a pointer to the beginning of the next word in a string
**
**		str - moves to the beginning of the after next word
**
**		in case of no words - return 1st argument
**
**		"word" - any sequence of characters separated by: {' ', '\t'}
*/

char	*ft_nwrd(char **str)
{
	char	*ptr;

	while (**str == ' ' || **str == '\t')
		(*str)++;
	ptr = *str;
	while (**str != ' ' && **str != '\t' && **str != '\0')
		(*str)++;
	while (**str == ' ' || **str == '\t')
		(*str)++;
	return (ptr);
}

/*
**	Returns 1 if the next word in the line matches substr, otherwise 0
**
**		"word" - any sequence of characters separated by: {' ', '\t'}
**
**		if substr is empty and there are no words in the line will return 1
*/

int		ft_isnwrd(char *str, char *substr)
{
	while (*str == ' ' || *str == '\t')
		str++;
	if (*substr == '\0' && *str == '\0')
		return (1);
	while (*str == *substr)
	{
		str++;
		substr++;
		if (*substr == '\0')
			return (*str == '\0' || *str == ' ' || *str == '\t');
	}
	return (0);
}

/*
** 	Returns 1 if the next word starts with any character in set, otherwise 0
**
**		"word" - any sequence of characters separated by: {' ', '\t'}
*/

int		ft_chnwrd(const char *str, const char *set)
{
	while (*str == ' ' || *str == '\t')
		str++;
	while (*set++ != '\0')
	{
		if (*set == *str)
			return (1);
	}
	return (0);
}
