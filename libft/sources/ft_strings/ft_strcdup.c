/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:28:52 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:18:15 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *str, char ch)
{
	size_t	len;
	char	*result;

	if (!str)
		return (NULL);
	result = NULL;
	len = 0;
	while (str[len] != '\0' && str[len] != ch)
		len++;
	result = (char *)ft_calloc(++len, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, len);
	return (result);
}
