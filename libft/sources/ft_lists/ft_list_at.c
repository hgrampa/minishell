/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:17:46 by hgrampa           #+#    #+#             */
/*   Updated: 2021/02/08 10:21:00 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_at(t_list *root, int index)
{
	while (index-- > 0)
	{
		if (root->next == NULL)
			return (NULL);
		root = root->next;
	}
	return (root);
}
