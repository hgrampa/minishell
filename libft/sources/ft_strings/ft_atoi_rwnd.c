/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_rwnd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:41:31 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/28 12:52:50 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pass_empty(char **str)
{
	while (**str == '\n' || **str == ' ' || **str == '\v'
		|| **str == '\t' || **str == '\r' || **str == '\f')
		(*str)++;
}

int	ft_atoi_rwnd(char **str)
{
	unsigned long	result;
	int				signature;

	result = 0;
	signature = 1;
	pass_empty(str);
	if (**str == '+')
		(*str)++;
	else if (**str == '-')
	{
		signature = -1;
		(*str)++;
	}
	while (**str >= '0' && **str <= '9')
		result = result * 10 + (*(*str)++ - '0');
	return ((int)(result * signature));
}
