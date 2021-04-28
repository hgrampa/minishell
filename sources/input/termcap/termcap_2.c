/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:30:03 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 12:26:58 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "errors.h"

int	term_on_new_line(t_terminal *term)
{
	tputs(save_cursor, 1, ft_putchar);
	if (!term_set_mode(term))
		return (err_print(NULL, 0, 1));
	return (1);
}

int	term_clear_line(void)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(clr_eos, 1, ft_putchar);
	return (1);
}
