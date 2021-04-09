/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:51:45 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:19:16 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= _FT_ALFADWN_MIN && c <= _FT_ALFADWN_MAX)
		c -= _FT_ASCII_ALFAREG_OFFSET;
	return (c);
}
