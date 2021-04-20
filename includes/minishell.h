/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:04:32 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/20 14:03:31 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/errno.h>
# include <termios.h>
# include <sys/errno.h>
# include <sys/errno.h>

# include "libft.h"
# include "environment.h"
# include "input.h"
# include "history.h"

# define _MINISHELL_TITLE "minishell"

typedef struct	s_minishell
{
	char			*title; 
	t_env			*env;
	t_input			*input;
	t_history		*history;
	unsigned long	rand_next;
	// история
	// мб билдыны
}				t_minishell;

// TODO пристроить куда-нибудь
int	ft_putchar(int c);

t_minishell	*minishell_create(const char *title, const char **envp);
int			minishell_init(t_minishell *shell);
int			minishell_on_exit(t_minishell *shell);
int			minishell_destroy(t_minishell *shell);
int			minishell_write_title(t_minishell *shell);

#endif

