/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:07:39 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/20 18:09:27 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	keycall_up_arrow(t_minishell *shell)
{
	//	Получаем пред строку из истории
	//	Если она == NULL
	// 		Печатаем bell
	// 	Иначе
	//		Возвращаем каретку в начало ввода
	tputs(restore_cursor, 1, ft_putchar);
	//		Очистка всего что поле курсора
	tputs(clr_eos, 1, ft_putchar);
	//		Вставляем след строку истории
	ft_putstr_fd("up", 1);
	// shell->input->line_len += ft_strlen(line)
}

void	keycall_dw_arrow(t_minishell *shell)
{
	//	Получаем пред строку из истории
	//	Если она == NULL
	// 		Печатаем bell
	// 	Иначе
	//		Возвращаем каретку в начало ввода
	tputs(restore_cursor, 1, ft_putchar);
	//		Очистка всего что поле курсора
	tputs(clr_eos, 1, ft_putchar);
	//		Вставляем пред строку истории
	ft_putstr_fd("down", 1);
	// shell->input->line_len += ft_strlen(line)
}

void	keycall_backspace(t_minishell *shell)
{
	if (shell->input->line_len > 0)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(clr_eos, 1, ft_putchar);
		shell->input->line_len--;
	}
}
