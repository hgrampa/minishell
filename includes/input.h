/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:43:36 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/13 18:56:47 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <unistd.h>
# include <termios.h>
# include "libft.h"

# define INP_READ_BUFFSIZE 1024

typedef struct s_input
{
	char			*buffer;
	ssize_t			size;
	struct termios	tattr;
	struct termios	tsave;
}				t_input;

int		input_read(t_input *input);
int		input_has_next_line(t_input *input, int *index);
t_input	*input_create(void);
int		input_get_next_line(t_input *input, char **line);
int		input_destroy(t_input *input);
void	input_reset_mode(t_input *input);
void	input_set_mode(t_input *input);

#endif
