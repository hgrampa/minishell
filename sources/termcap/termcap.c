/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:30:03 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/18 18:41:31 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <term.h>
// #include <curses.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "libft.h"


// static char term_buffer [2048]; 

typedef struct	s_term
{
	struct termios	termios;
	struct termios	save_termios;
}				t_term;

int		ft_putchar(int	c)
{
	return (write(1, &c, 1));
}

void	term_up_arrow()
{
	//  очистка линии
	// Возвращаем каретку в начало
	// Вставляем сдел строку истории
}

void	term_dw_arrow()
{
	// очистка линии
	// Возвращаем каретку в начало
	// Вставляем пред строку истории
}

void	term_backspace()
{
	tputs(cursor_left, 1, ft_putchar);
	tputs(clr_eos, 1, ft_putchar);
}

int		term_reset_mode(t_term *term)
{
	if (tcsetattr(0, TCSANOW, &term->save_termios) == -1)
		return (0);
	else
		return (1);
}

int		term_set_mode(t_term *term)
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
	return (1);
}

t_term	*term_create(void)
{
	t_term	*term;

	term = (t_term *)ft_calloc(1, sizeof(t_term));
	if (term == NULL)
		return (NULL);
	return (term);
}

int		term_init(t_term *term)
{
	int		success;
	char	*term_type;

	term_type = getenv("TERM");
	if (!isatty(STDIN_FILENO))
	{
		printf("Not a terminal\n");
		return (0);
	}
	if (term_type == NULL)
	{
		printf("Failed to get the name of the terminal. Set environment variable TERM\n");  // TODO код возврата
		return (0);
	}
	success = tgetent(NULL, term_type);
	if (success < 1)
	{
   		printf("Could not access the termcap data base or terminal type is not defined.\n"); // TODO код возврата
		return (0);
	}
	return(term_set_mode(term));
}

int		term_destroy(t_term *term)
{
	free(term);
	return (1);
}

int main(int argc, char const *argv[])
{
	t_term	*term;
	char	buff[256];
	ssize_t read_len;

	term = term_create();
	if (!term_init(term))
		exit(1);
	while (21)
	{
		ft_bzero(buff, 256 * sizeof(char));
		read_len = read(0, buff, 255);
		write(1, buff, read_len);
		// if (buff[read_len - 1] == '\n') // вообще в строке а не так но мне похуй
		// 	break ;
	}
	return 0;
}
