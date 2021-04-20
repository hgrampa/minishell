/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 18:43:36 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/20 11:11:41 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <unistd.h>
# include "libft.h"
# include "sbuffer.h"
# include "terminal.h"

# define _INP_STR_BUFFSIZE 80
# define _INP_READ_BUFFSIZE 1024

typedef struct s_input
{
	t_sbuffer		*buffer;
	t_terminal		*term;
}				t_input;

int		input_read(t_input *input);
int		input_has_next_line(t_input *input, int *index);
t_input	*input_create(void);
int		input_get_next_line(t_input *input, char **line);
int		input_destroy(t_input *input);

#endif
