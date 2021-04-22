/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_factory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:14:31 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 21:58:56 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "com_factory.h"



// typedef struct	s_state_machne
// {
// 	int	process;
// 	int	(*current_state)(struct	s_statemachne*, char*);

// }				t_state_machne;

// int state1(t_state_machne *machine, char *line)
// {
// 	line[0] = 'a';
// 	machine->current_state = state2;
// 	return (1)
// }

// int state2(t_state_machne *machine, char *line)
// {
// 	free(line);
// 	machine->process = 0;
// 	return (1)
// }

// void foo(char *line)
// {
// 	t_state_machne machine;

// 	machine.process = 1;
// 	machine.current_state = state1;
// 	while (machine.process)
// 	{
// 		machine.current_state(&machine, line);
// 	}
// }

// line[0] = 'a';
// free(line);
// return;


int	com_factory_run_line(t_list *words, t_minishell *shell)
{
	return (1);
}
