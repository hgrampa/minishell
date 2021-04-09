/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:42:32 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:16:25 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*result;

	size *= count;
	result = (unsigned char *)malloc(size);
	if (!result)
		return (NULL);
	while (size-- > 0)
		result[size] = '\0';
	return (result);
}
