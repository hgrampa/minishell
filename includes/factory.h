/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:24:23 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/24 20:32:15 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_H
# define FACTORY_H

# include "libft.h"
# include "pword.h"
# include "minishell.h"

typedef struct	s_command
{
	char			*path;
	t_list			*argv;
	char			is_pipe:1;
	int				pipe[2];
	int				in_fd;
	int				out_fd;
}				t_command;

// TODO bash: syntax error near unexpected token `|'
// TODO bash: syntax error near unexpected token `;'
// TODO bash: dfs: command not found

struct s_build_context
{
	t_command	*command;
	int			process:1;
};


typedef struct	s_factory
{
	t_dlist		*commands;
	int			result;
	char		*env_path; // TODO потом убрать
	char		**paths;
}				t_factory;

int	factory_run_line(t_list *words, t_minishell *shell);
int factory_build_commands(t_factory *factory, t_list *words, t_minishell *shell);
int factory_exec_commands(t_factory *factory, t_minishell *shell);
char *factory_find_path(t_factory *factory, char *bin);

#endif
