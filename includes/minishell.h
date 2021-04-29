/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:04:32 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 14:09:15 by hgrampa          ###   ########.fr       */
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
# include <fcntl.h>

# include "libft.h"
# include "environment.h"
# include "input.h"
# include "history.h"
# include "factory.h"
# include "pword.h"
# include "exit_code.h"

# define _MINISHELL_TITLE "minishell"

typedef struct s_minishell
{
	unsigned char	process :1;
	char			*title;
	t_env			*env;
	t_input			*input;
	t_history		*history;
	t_factory		*factory;
	unsigned long	rand_next;
	t_list			*words;
	char			*line;
}				t_minishell;

t_minishell	*minishell_create(const char *title, const char **envp);
int			minishell_init(t_minishell *shell);
int			minishell_on_exit(t_minishell *shell);
int			minishell_destroy(t_minishell *shell);
int			minishell_write_title(t_minishell *shell);
int			minishell_at_newline(t_minishell *shell);
void		minishell_exit(t_minishell *shell, int status);

void		minishell_signal_int(int signum);
void		minishell_signal_quit(int signum);

#endif
