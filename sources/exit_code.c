/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:00:07 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/24 13:28:18 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	g_exit_code;

void	exit_code_set(int code)
{
	g_exit_code = code;
}

int exit_code_get(void)
{
	return (g_exit_code);
}
