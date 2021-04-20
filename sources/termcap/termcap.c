/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:30:03 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/20 23:53:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

int		term_reset_mode(t_terminal *term)
{
	if (tcsetattr(0, TCSANOW, &term->save_termios) == -1)
		return (0);
	else
		return (1);
	tputs(keypad_local, 1, ft_putchar);
}

int		term_set_mode(t_terminal *term)
{
	if (tcgetattr(0, &term->save_termios) == -1)
	{
		// perror("fdfg");
		return (0); // TODO код возврата
	}
	ft_memcpy(&term->termios, &term->save_termios, sizeof(struct termios));
	term->termios.c_lflag &= ~(ECHO|ICANON);
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term->termios) == -1)
	{
		// printf("2\n");
		return (0); // TODO код возврата
	}
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

int		term_init(t_terminal *term)
{
	int		success;
	char	*term_type;

	// term_type = getenv("TERM");
	// !!! TODO Убрать
	term_type = "xterm-256color";
	if (!isatty(STDIN_FILENO))
	{
		printf("Not a terminal\n");
		return (0);
	}
	if (term_type == NULL)
	{
		printf("Failed to get the name of the terminal. Set environment variable TERM\n"); // TODO код возврата
		return (0);
	}
	success = tgetent(NULL, term_type);
	if (success < 1)
	{
   		printf("Could not access the termcap data base or terminal type is not defined.\n"); // TODO код возврата
		return (0);
	}
	if (!term_set_mode(term))
	{
		return (0); // TODO код возврата
	}
	return(1);
}

int		term_destroy(t_terminal *term)
{
	free(term);
	return (1);
}

int		term_on_new_line(void)
{
	tputs(save_cursor, 1, ft_putchar);
	return (1);
}


int		term_is_key_muted(char *buff, ssize_t len)
{
	// || ft_strncmp(buff, key_exit, len) == 0
	return (ft_strncmp(buff, key_right, len) == 0
		|| ft_strncmp(buff, key_left, len) == 0
		|| ft_strncmp(buff, key_ppage, len) == 0 
		|| ft_strncmp(buff, key_npage, len) == 0
		|| ft_strncmp(buff, key_home, len) == 0 
		|| ft_strncmp(buff, key_end, len) == 0);
}

enum e_key_type	term_key_type(char *buff, ssize_t len)
{
	if (ft_strncmp(buff, "\177", len) == 0)
	{
		return (EKT_BACKSPACE);
	}
	else if (term_is_key_muted(buff, len))
	{
		return (EKT_MUTED);
	}
	else if (ft_strncmp(buff, key_up, len) == 0)
	{
		return (EKT_UPARR);
	}
	else if (ft_strncmp(buff, key_down, len) == 0)
	{
		return (EKT_DWARR);
	}
	else
	{
		return (EKT_NOTKEY);
	}
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
