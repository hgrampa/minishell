/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:34:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/24 13:55:06 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <signal.h>
#include "factory.h"

void	signal_handler(int signum)
{
	int status;

	wait(&status);
	if (status == SIGINT)
	{
		// exit_code_set(130);
	}
	else if (status == SIGQUIT)
	{
		// exit_code_set(131);
	}
	// else if (signum == )
	// {

	// }

}