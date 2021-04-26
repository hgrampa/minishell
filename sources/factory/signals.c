/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:34:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/26 18:33:48 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include "factory.h"
#include "exit_code.h"

void	signal_quit_handler(int signum)
{
	int status;

	wait(&status);
	exit_code_set(128 + status);
	printf("Quit: %d\n", signum);
}

void	signal_int_handler(int signum)
{
	int status;

	wait(&status);
	exit_code_set(128 + status);
	ft_putchar('\n');
}
