/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:30:03 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/18 13:19:16 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <termcap.h>
#include <stdlib.h>
#include <termios.h>

// static char term_buffer [2048]; 

typedef struct	s_termsettings
{
	struct termios	cur_attributes;
	struct termios	org_attributes;
}				t_termsettings;

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
	// Получить ширину окна
	// Получить ширину окна что была раньше
	// Получить кол считанных символов (до \n)
	
	// Узнать тек строку ((index + lable_len) / wigth)
	// Узнать тек колонку ((index + lable_len) % wigth)

	// Если тек колонка - 0 && тек строка > 0
	//  tputs(tgetstr("up", &buff), 1, ft_putchar);
	//  tputs(tgoto(tgetstr("ch", NULL), 0, wight (wight-1), 1, ft_putchar)
	//  tputs(tgetstr("dc", &buff), 1, ft_putchar);
	// Иначе
	// 	tputs(tgetstr("le", &buff), 1, ft_putchar);
	//  tputs(tgetstr("dc", &buff), 1, ft_putchar);


}

// Считать ввод пользователя
// Начти там УС
// 	Отработать / Удаляем УС 




void input_reset_mode(t_termsettings *term)
{
	tcsetattr(0, TCSANOW, &term->org_attributes);
}

void input_set_mode(t_termsettings *term)
{

	tcgetattr(0, &term->org_attributes);
	memcpy(&term->cur_attributes, &term->org_attributes, sizeof(struct termios));
	
	/* включаем неканонический режим без эха */
	term->cur_attributes.c_lflag &= ~(ICANON|ECHO);
	/* считываем минимум по одному символу */
	term->cur_attributes.c_cc[VMIN] = 1;
	term->cur_attributes.c_cc[VTIME] = 0;

	tcsetattr(0, TCSAFLUSH, &term->cur_attributes);
}

int main(int argc, char const *argv[])
{
	char			*term_type;
	int				success;
	char			term_buffer [2048];
	t_termsettings	term;

	char c;
	int	top_input_index;

	printf("result = %d\n", 6 % 6);
	exit(1);

	top_input_index = 0;
	while (21)
	{
		top_input_index += read(0, &c, 1);
		if (c == '\n')
			break;
		write(1, &c, 1);
	}

	term_type = getenv("TERM");
	if (term_type == NULL)
	{
		printf("Failed to get the name of the terminal. Set environment variable TERM\n");
		return (1);
	}
	success = tgetent(term_buffer, term_type);
	if (success < 1)
	{
   		printf("Could not access the termcap data base or terminal type is not defined.\n");
		return (1);
	}

	return 0;
}
