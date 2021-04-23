/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:07:39 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 18:54:53 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <termios.h>
#include "minishell.h"
#include "keymap.h"
#include "history.h"
#include "sbuffer.h"

int		call_bell(void)
{
	tputs(bell, 1, ft_putchar);
	return (1);
}

int		keycall_up_arrow(t_minishell *shell)
{
	char *line;

	line = history_up(shell->history);
	if (line == NULL)
		return (call_bell());
	input_save_line(shell->input);
	return (input_set_line(shell->input, line));
}

int		keycall_dw_arrow(t_minishell *shell)
{
	char *line;

	line = history_down(shell->history);
	if (line == NULL)
	{
		if (shell->input->save_line != NULL)
			return (input_restore_save_line(shell->input));
		else
			return (call_bell());
	}
	return (input_set_line(shell->input, line));
}

int		input_set_line(t_input *input, char *line)
{
	term_clear_line();	

	ft_putstr_fd(line, STDOUT_FILENO);
	sbuffer_clear(input->buffer);
	sbuffer_add_str(input->buffer, line);
	input->line_len = ft_strlen(line);
	return (1);
}

int		input_save_line(t_input *input)
{
	if (input->save_line == NULL)
	{
		input->save_line = ft_strdup(input->buffer->str);
		if (input->save_line == NULL)
			return (0); // TODO возврат ошибки
	}
	return (1);
}

int		input_restore_save_line(t_input *input)
{
	char *line;

	term_clear_line();
	line = input->save_line;
	ft_putstr_fd(line, STDOUT_FILENO);
	sbuffer_clear(input->buffer);
	sbuffer_add_str(input->buffer, line);
	input->line_len = ft_strlen(line);
	free(line);
	input->save_line = NULL;
	return (1);
}

int		keycall_backspace(t_minishell *shell)
{
	if (shell->input->line_len > 0)
	{
		sbuffer_backspace(shell->input->buffer);
		tputs(cursor_left, 1, ft_putchar);
		tputs(clr_eos, 1, ft_putchar);
		shell->input->line_len -= 1; // TODO если не ASCII символ то неккорктно работает
	}
	return (1);
}

int		keycall_cntrl_c(t_minishell *shell)
{
	write(1, "\n", 1);  // TODO омега костыль
	shell->input->abort = 1;
	return (1);
}

// TODO пишется ли команда exit в историю?
int		keycall_cntrl_d(t_minishell *shell)
{
	if (shell->input->line_len > 0)
		return (call_bell());
	input_set_line(shell->input, "exit\n");
	return (1);
}

int		input_take_key(enum e_key_type type, t_minishell *shell)
{
	if (type == EKT_MUTED)
		return (call_bell());
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
