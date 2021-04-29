/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:00:07 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 13:05:15 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	g_exit_code;

void	exit_code_set(int code)
{
	g_exit_code = code;
}

void	exit_code_clamp_set(int code)
{
	if (code == 256)
		exit_code_set(1);
	else if (code > 255)
		exit_code_set(code % 256);
	else
		exit_code_set(code);
}

int	exit_code_get(void)
{
	int	code;

	code = g_exit_code;
	exit_code_set(0);
	return (code);
}
