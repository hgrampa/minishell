/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:30:03 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/28 18:18:20 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "errors.h"

int	term_reset_mode(t_terminal *term)
{
	if (tcsetattr(0, TCSANOW, &term->save_termios) == -1)
		return (err_print(NULL, 0, 1));
	else
		return (1);
	tputs(keypad_local, 1, ft_putchar);
}

int	term_set_mode(t_terminal *term)
{
	if (tcgetattr(0, &term->save_termios) == -1)
	{
		return (0); // TODO код возврата
	}
	ft_memcpy(&term->termios, &term->save_termios, sizeof(struct termios));
	term->termios.c_lflag &= ~(ECHO | ICANON | ISIG);
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term->termios) == -1)
		return (0); // TODO код возврата
	tputs(keypad_xmit, 1, ft_putchar);
	return (1);
}

t_terminal	*term_create(void)
{
	t_terminal	*term;

	term = (t_terminal *)ft_calloc(1, sizeof(t_terminal));
	if (term == NULL)
		return (NULL);
	return (term);
}

int	term_init(void)
{
	int		success;
	char	*term_type;

	term_type = getenv("TERM");
	if (!isatty(STDIN_FILENO))
		return (err_print(_ERR_NOTTERM, 0, 1));
	if (term_type == NULL)
		return (err_print(_ERR_NOTTERMENV, 0, 1));
	success = tgetent(NULL, term_type);
	if (success < 1)
		return (err_print(_ERR_NOTTERMTYPE, 0, 1));
	// TODO необходимо добавить признак того что растройки восстановленны
	// 	если при чтении возникнет ошибка и в обработке исключения восстановить режим
	return (1);
}

int	term_destroy(t_terminal *term)
{
	free(term);
	return (1);
}	

// int main(int argc, char const *argv[])
// {
// 	t_terminal	*term;
// 	char	buff[256];
// 	ssize_t read_len;
// 	// 
// 	term = term_create();
// 	// printf("t_terminal = %lu\n", sizeof(t_terminal));
// 	if (!term_init(term))
// 		exit(1);
// 	// в начале ввода команды
// 	tputs(save_cursor, 1, ft_putchar);
// 	while (21)
// 	{
// 		ft_bzero(buff, 256 * sizeof(char));
// 		read_len = read(0, buff, 255);
// 		term_take_input(buff, read_len);
// 	}
// 	return 0;
// }
