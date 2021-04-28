/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:34:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/28 18:17:21 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <stdio.h>
#include "minishell.h"

void	minishell_signal_quit(int signum)
{
	int	status;

	wait(&status);
	exit_code_set(128 + status);
	printf("Quit: %d\n", signum);
	signum = 0;
}

void	minishell_signal_int(int signum)
{
	int	status;

	wait(&status);
	exit_code_set(128 + status);
	ft_putchar('\n');
	signum = 0;
}
