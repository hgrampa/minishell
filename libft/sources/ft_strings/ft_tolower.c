/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:51:51 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:19:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= _FT_ALFAUP_MIN && c <= _FT_ALFAUP_MAX)
		c += _FT_ASCII_ALFAREG_OFFSET;
	return (c);
}
