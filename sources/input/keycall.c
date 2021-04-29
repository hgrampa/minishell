/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:07:39 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 14:07:29 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <termios.h>
#include "minishell.h"
#include "keymap.h"
#include "history.h"
#include "sbuffer.h"

int	keycall_up_arrow(t_minishell *shell)
{
	char	*line;

	line = history_up(shell->history);
	if (line == NULL)
		return (keycall_bell());
	if (!input_save_line(shell->input))
		return (1);
	return (input_set_line(shell->input, line));
}

int	keycall_dw_arrow(t_minishell *shell)
{
	char	*line;

	line = history_down(shell->history);
	if (line == NULL)
	{
		if (shell->input->save_line != NULL)
			return (input_restore_save_line(shell->input));
		else
			return (keycall_bell());
	}
	return (input_set_line(shell->input, line));
}

int	keycall_backspace(t_minishell *shell)
{
	if (shell->input->line_len > 0)
	{
		sbuffer_backspace(shell->input->buffer);
		tputs(cursor_left, 1, ft_putchar);
		tputs(clr_eos, 1, ft_putchar);
		shell->input->line_len -= 1;
	}
	return (1);
}

int	keycall_cntrl_c(t_minishell *shell)
{
	write(1, "\n", 1);
	exit_code_set(1);
	shell->input->abort = 1;
	return (1);
}

int	keycall_cntrl_d(t_minishell *shell)
{
	if (shell->input->line_len > 0)
		return (keycall_bell());
	input_set_line(shell->input, "exit\n");
	shell->input->abort = 1;
	shell->process = 0;
	return (1);
}
