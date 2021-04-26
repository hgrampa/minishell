/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 13:50:37 by hgrampa           #+#    #+#             */
/*   Updated: 2020/12/28 14:48:38 by hgrampa          ###   ########.fr       */
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

static double	fraction(const char *str)
{
	double	result;
	int		e;

	result = 0.0;
	e = 0;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str++ - _FT_ASCII_NUM_OFFSET);
		e--;
	}
	while (e++ < 0)
		result *= 0.1;
	return (result);
}

/*
**	Function converts string to double
**
**		! relative error after 19 characters
*/

double	ft_atof(const char *str)
{
	double	result;
	char	sign;

	result = 0.0;
	sign = 1;
	str = pass_empty(str);
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '+')
		str++;
	while (*str == '0')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - _FT_ASCII_NUM_OFFSET);
	if (*str == '.')
		result += fraction(++str);
	return (result * (double)sign);
}
