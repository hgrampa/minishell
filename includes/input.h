/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:43:36 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/28 18:19:07 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <unistd.h>
# include "libft.h"
# include "sbuffer.h"
# include "terminal.h"
# include "keymap.h"

# define _INP_STR_BUFFSIZE 80
# define _INP_READ_BUFFSIZE 32

typedef struct s_input
{
	t_sbuffer		*buffer;
	char			*save_line;
	t_terminal		*term;
	int				line_len;
	unsigned char	abort :1;
}				t_input;

typedef struct s_minishell	t_minishell;

t_input	*input_create(void);
int		input_destroy(t_input *input);
int		input_init(void);
int		input_get_next_line(t_input *input, char **line, t_minishell *shell);
int		input_take_key(enum e_key_type type, t_minishell *shell);

int		input_set_line(t_input *input, char *line);
int		input_save_line(t_input *input);
int		input_restore_save_line(t_input *input);

int		keycall_bell(void);
int		keycall_up_arrow(t_minishell *shell);
int		keycall_dw_arrow(t_minishell *shell);
int		keycall_backspace(t_minishell *shell);
int		keycall_cntrl_c(t_minishell *shell);
int		keycall_cntrl_d(t_minishell *shell);

#endif
