/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 12:02:29 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/15 12:15:20 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, ssize_t new_size)
{
	void	*result;

	if (ptr == NULL)
		return (malloc(new_size));
	result = malloc(new_size);
	ft_memcpy(result, ptr, old_size);
	free(ptr);
	return (result);
}
