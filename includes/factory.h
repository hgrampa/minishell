/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:24:23 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/25 18:48:44 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_H
# define FACTORY_H

# include "libft.h"
# include "pword.h"
# include "minishell.h"
# include "command.h"
# include "buildin.h"
# include "errors.h"


#define _PIPE_SIDE_OUT 0
#define _PIPE_SIDE_IN 1

// TODO bash: syntax error near unexpected token `|'
// TODO bash: syntax error near unexpected token `;'
// TODO bash: dfs: command not found



struct s_build_context
{
	t_command		*command;
	t_list			*argl;
	unsigned char	process:1;
};

typedef struct	s_factory
{
	t_dlist		*commands;
	int			result;
	char		*env_path; // TODO потом убрать
	char		**paths;
}				t_factory;

struct s_comm_pair
{
	t_command		*command;
	t_command		*previous;
};


int	factory_destroy(t_factory *factory);
int	factory_init(t_factory *factory, t_minishell *shell);

int	factory_run_line(t_list *words, t_minishell *shell);
int factory_build_commands(t_factory *factory, t_list *words, t_minishell *shell);
int factory_exec_commands(t_factory *factory, t_minishell *shell);
char *factory_find_path(t_factory *factory, char *bin);

int	factory_command_set_pipe(t_list **words, struct s_build_context *context);
int	factory_command_set_semicolon(t_list **words,
	struct s_build_context *context);
int	factory_command_set_input(t_list **words, struct s_build_context *context);
int	factory_command_set_output(t_list **words, struct s_build_context *context,
	int to_end);
int	factory_command_set_argv(t_pword *word, struct s_build_context *context);

#endif
