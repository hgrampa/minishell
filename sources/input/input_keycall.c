/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_keycall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:21:19 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/24 11:26:26 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keymap.h"

int	keycall_bell(void)
{
	tputs(bell, 1, ft_putchar);
	return (1);
}

int	input_take_key(enum e_key_type type, t_minishell *shell)
{
	if (type == EKT_MUTED)
		return (keycall_bell());
	else if (type == EKT_BACKSPACE)
		return (keycall_backspace(shell));
	else if (type == EKT_DWARR)
		return (keycall_dw_arrow(shell));
	else if (type == EKT_UPARR)
		return (keycall_up_arrow(shell));
	else if (type == EKT_CNTRLD)
		return (keycall_cntrl_d(shell));
	else if (type == EKT_CNTRLC)
		return (keycall_cntrl_c(shell));
	else
		return (0);
}
