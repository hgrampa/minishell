/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:04:04 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/28 18:18:29 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <unistd.h>
# include <term.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include "libft.h"
# include "keymap.h"

typedef struct s_terminal
{
	struct termios	termios;
	struct termios	save_termios;
}				t_terminal;

t_terminal		*term_create(void);
int				term_init(void);
int				term_destroy(t_terminal *term);
int				term_reset_mode(t_terminal *term);
int				term_set_mode(t_terminal *term);
int				term_on_new_line(t_terminal *term);
enum e_key_type	term_key_type(char *buff, ssize_t len);
int				term_clear_line(void);

#endif
