/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:07:39 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/21 01:02:04 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <termios.h>
#include "minishell.h"
#include "keymap.h"
#include "history.h"
#include "sbuffer.h"

int		keycall_up_arrow(t_minishell *shell)
{
	char *line;

	line = history_up(shell->history);
	if (line == NULL)
		return (call_bell());
	if (shell->input->save_line == NULL)
		shell->input->save_line = ft_strdup(shell->input->buffer->str); // TODO Возврат ошибки
	// 	Иначе
	//		Возвращаем каретку в начало ввода
	tputs(restore_cursor, 1, ft_putchar);
	//		Очистка всего что поле курсора
	tputs(clr_eos, 1, ft_putchar);
	//		Вставляем пред строку истории
	ft_putstr_fd(line, STDOUT_FILENO);
	// 		И в буфер
	sbuffer_clear(shell->input->buffer);
	sbuffer_add_str(shell->input->buffer, line);
	shell->input->line_len += ft_strlen(line);
	return (1);
}

int		keycall_dw_arrow(t_minishell *shell)
{
	char *line;

	//	Получаем пред строку из истории
	line = history_down(shell->history);
	//	Если она == NULL
	if (line == NULL)
	{
		if (shell->input->save_line != NULL)
		{
			sbuffer_add_str(shell->input->buffer, shell->input->save_line);
			free(shell->input->save_line);
			shell->input->save_line = NULL;
			return (1);
		}
		else
			return (call_bell());
	}
	// 	Иначе
	//		Возвращаем каретку в начало ввода
	tputs(restore_cursor, 1, ft_putchar);
	//		Очистка всего что поле курсора
	tputs(clr_eos, 1, ft_putchar);
	//		Вставляем пред строку истории
	ft_putstr_fd(line, STDOUT_FILENO);
	sbuffer_clear(shell->input->buffer);
	sbuffer_add_str(shell->input->buffer, line);
	shell->input->line_len += ft_strlen(line);
	return (1);
}

int		keycall_backspace(t_minishell *shell)
{
	if (shell->input->line_len > 0)
	{
		// TODO Добавить удаление чара из буфера
		sbuffer_backspace(shell->input->buffer);
		tputs(cursor_left, 1, ft_putchar);
		tputs(clr_eos, 1, ft_putchar);
		shell->input->line_len -= 1; // TODO если не ASCII символ то неккорктно работает
	}
	return (1);
}

int		call_bell(void)
{
	tputs(bell, 1, ft_putchar);
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
	else
		return (0);
}
