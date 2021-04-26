/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:37:17 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:17:54 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= _FT_ALFAUP_MIN && c <= _FT_ALFAUP_MAX)
		|| (c >= _FT_ALFADWN_MIN && c <= _FT_ALFADWN_MAX));
}
