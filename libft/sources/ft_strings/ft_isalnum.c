/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:42:44 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:17:51 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= _FT_DIGIT_MIN && c <= _FT_DIGIT_MAX)
		|| (c >= _FT_ALFAUP_MIN && c <= _FT_ALFAUP_MAX)
		|| (c >= _FT_ALFADWN_MIN && c <= _FT_ALFADWN_MAX));
}
