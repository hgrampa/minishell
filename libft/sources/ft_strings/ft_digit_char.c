/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 12:23:26 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:17:32 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_digit_char_lw(int digit)
{
	if (digit < 10)
		return (_FT_ASCII_NUM_OFFSET + digit);
	else
	{
		digit %= 10;
		return (_FT_ALFADWN_MIN + digit);
	}
}

char	ft_digit_char_up(int digit)
{
	if (digit < 10)
		return (_FT_ASCII_NUM_OFFSET + digit);
	else
	{
		digit %= 10;
		return (_FT_ALFAUP_MIN + digit);
	}
}
