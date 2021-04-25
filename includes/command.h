/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:35:57 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/25 18:48:35 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "buildin.h"

typedef struct	s_command
{
	char			*name;
	// t_list			*argl;
	// TODO массив аргументов
	char			**argv;
	unsigned char	is_pipe:1;
	unsigned char	is_buildin:1;
	int				pipe[2];
	int				input;
	int				output;
	t_buildin		buildin;
}				t_command;

t_command *command_create(char *name);
int	command_destroy(t_command *command);
void	command_set_buildin(t_command *command, t_buildin buildin);
void	command_print_argv(void *data);
void	command_print(void *data);

#endif
