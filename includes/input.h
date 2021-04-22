/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:43:36 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/21 15:13:31 by hgrampa          ###   ########.fr       */
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
# define _INP_READ_BUFFSIZE 1024

typedef struct s_input
{
	t_sbuffer		*buffer;
	char			*save_line;
	t_terminal		*term;
	int				line_len;
}				t_input;

typedef struct s_minishell	t_minishell;

t_input	*input_create(void);
int		input_destroy(t_input *input);
int		input_init(t_input *input);
int		input_read(t_input *input, t_minishell *shell);
int		input_get_next_line(t_input *input, char **line, t_minishell *shell);
int		input_take_key(enum e_key_type type, t_minishell *shell);

int		input_set_line(t_input *input, char *line);
int		input_save_line(t_input *input);
int		input_restore_save_line(t_input *input);

#endif
