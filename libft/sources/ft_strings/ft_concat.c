/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:50:11 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/13 18:50:31 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_concat2(char *str1, char *str2)
{
	size_t	len1;
	size_t	len2;
	char	*tmp;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	result = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	tmp = result;
	ft_strncat(tmp, str1, len1);
	tmp += len1;
	ft_strncat(tmp, str2, len2);
	return (result);
}

char	*ft_concat3(char *str1, char *str2, char *str3)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*tmp;
	char	*result;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	len3 = ft_strlen(str3);
	result = (char *)ft_calloc(len1 + len2 + len3 + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	tmp = result;
	ft_strncat(tmp, str1, len1);
	tmp += len1;
	ft_strncat(tmp, str2, len2);
	tmp += len2;
	ft_strncat(tmp, str3, len3);
	return (result);
}
