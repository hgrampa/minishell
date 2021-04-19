/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:30:03 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/19 11:11:47 by hgrampa          ###   ########.fr       */
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

# define _KEY_SET_LENGTH 12

typedef struct	s_key_setting
{
	char	*key;
	int		(*call)(void);
}				t_key_setting;

typedef struct	s_term
{
	struct termios	termios;
	struct termios	save_termios;
	t_key_setting	keys_settings[_KEY_SET_LENGTH];		

}				t_term;

int		ft_putchar(int	c)
{
	return (write(1, &c, 1));
}

void	key_call_up_arrow()
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
}

void	key_call_dw_arrow()
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
}

void	key_call_backspace()
{
	tputs(cursor_left, 1, ft_putchar);
	tputs(clr_eos, 1, ft_putchar);
}

// t_key_setting	*key_setting_create(const char *key, int (*call)(void))
// {
// 	t_key_setting	*new;

// 	new = (t_key_setting *)ft_calloc(1, sizeof(t_key_setting));
// 	if (new == NULL)
// 		return (NULL);
// 	new->key = ft_strdup(key);
// 	if (new->key == NULL)
// 	{
// 		free(new);
// 		return (NULL);
// 	}
// 	new->call = call;
// 	return (new);
// }

// int		keys_settings_init(t_term *term)
// {
// 	t_key_setting *setting;
	
// 	setting = key_setting_create("\177", term_backspace);
// 	if (setting == NULL)
// 		return (0);
// 	term->keys_settings[0] = setting;
// 	return (1);
// }


int		term_reset_mode(t_term *term)
{
	if (tcsetattr(0, TCSANOW, &term->save_termios) == -1)
		return (0);
	else
		return (1);
	tputs(keypad_local, 1, ft_putchar);
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
	tputs(keypad_xmit, 1, ft_putchar);
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

	// term_type = getenv("TERM");
	term_type = "xterm-256color"; // !!! TODO вернуть реальный тип терминала
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

int		term_destroy(t_term *term)
{
	free(term);
	return (1);
}

int		term_is_key_muted(char *buff, ssize_t len)
{
	// || ft_strncmp(buff, key_exit, len) == 0
	return (ft_strncmp(buff, key_right, len) == 0
		|| ft_strncmp(buff, key_left, len) == 0
		|| ft_strncmp(buff, key_ppage, len) == 0 // TODO эти не работают eny way
		|| ft_strncmp(buff, key_npage, len) == 0); // TODO эти не работают eny way
}

int		term_take_input(char *buff, ssize_t len)
{
	if (term_is_key_muted(buff, len))
	{
		tputs(bell, 1, ft_putchar);
	}
	else if (ft_strncmp(buff, "\177", len) == 0)
	{
		key_call_backspace();
	}
	else if (ft_strncmp(buff, key_up, len) == 0)
	{
		key_call_up_arrow();
	}
	else if (ft_strncmp(buff, key_down, len) == 0)
	{
		key_call_dw_arrow();
	}
	else
		write(STDOUT_FILENO, buff, len);
	return (1);
}

int main(int argc, char const *argv[])
{
	t_term	*term;
	char	buff[256];
	ssize_t read_len;

	term = term_create();
	// printf("t_term = %lu\n", sizeof(t_term));
	if (!term_init(term))
		exit(1);
	// в начале ввода команды
	tputs(save_cursor, 1, ft_putchar);
	while (21)
	{
		ft_bzero(buff, 256 * sizeof(char));
		read_len = read(0, buff, 255);
		term_take_input(buff, read_len);
	}
	return 0;
}
