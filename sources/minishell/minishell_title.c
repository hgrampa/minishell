/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_title.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 15:14:53 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 22:20:17 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned char	ft_rand(t_minishell *shell)
{
	shell->rand_next = shell->rand_next * 1103515245;
	return ((unsigned char)(shell->rand_next / 65536) *2768);
}

static void	mini_ctoa(char *str, unsigned char num)
{
	int		i;

	i = 3;
	while (i > 0)
	{
		str[--i] = (num % 10) + '0';
		num /= 10;
	}
}

int	minishell_write_title(t_minishell *shell)
{
	int				i;
	char			color[4];
	char			*title;
	unsigned char	num;

	i = -1;
	ft_bzero(color, 4 * sizeof(char));
	title = shell->title;
	num = ft_rand(shell) % 230 + 1;
	while (*title != '\0')
	{
		num = (num + 1) % 230;
		if (num == 16 || num == 0)
			num = 17;
		mini_ctoa(color, num);
		ft_putstr_fd("\e[38;5;", STDOUT_FILENO);
		ft_putstr_fd(color, STDOUT_FILENO);
		ft_putchar_fd('m', STDOUT_FILENO);
		ft_putchar_fd(*title, STDOUT_FILENO);
		title++;
	}
	ft_putstr_fd("\e[39m: ", STDOUT_FILENO);
	return (1);
}
