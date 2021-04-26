/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:41:31 by hgrampa           #+#    #+#             */
/*   Updated: 2020/12/28 14:28:20 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*pass_empty(const char *str)
{
	while (*str == 32 || *str == 0 || *str == 10 || *str == 11 || *str == 12
		|| *str == 13)
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				sign;

	result = 0;
	sign = 1;
	str = pass_empty(str);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (result > _FT_SINT64_MAX)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		result = result * 10 + (*str++ - _FT_ASCII_NUM_OFFSET);
	}
	return ((int)(result * sign));
}
