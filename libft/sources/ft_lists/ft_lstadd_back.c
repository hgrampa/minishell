/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:43:17 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:16:34 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*slider;

	if (lst && new)
	{
		slider = *lst;
		if (slider == NULL)
			*lst = new;
		else
		{
			while (slider->next != NULL)
				slider = slider->next;
			slider->next = new;
		}
	}
}
