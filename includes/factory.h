/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:24:23 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:38:44 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_H
# define FACTORY_H

# include "libft.h"
# include "pword.h"
# include "command.h"
# include "environment.h"
# include "buildin.h"
# include "errors.h"
# include "exit_code.h"

# define _PIPE_SIDE_OUT 0
# define _PIPE_SIDE_IN 1

typedef struct s_minishell	t_minishell;

struct s_build_context
{
	t_command		*command;
	t_list			*argl;
	unsigned char	process :1;
};

typedef struct s_factory
{
	t_dlist		*commands;
	int			result;
	char		**paths;
}				t_factory;

struct s_comm_pair
{
	t_command		*command;
	t_command		*previous;
};

t_factory			*factory_create(void);
int					factory_destroy(t_factory *factory);
int					factory_clear(t_factory *factory);
int					factory_init(t_factory *factory, t_minishell *shell);

int					factory_run_line(t_factory *factory, t_list *words,
						t_minishell *shell);
int					factory_build_commands(t_factory *factory, t_list *words);
int					factory_is_redirection(enum e_pword_type type);
int					factory_exec_commands(t_factory *factory,
						t_minishell *shell);
int					factory_biuld_command(t_factory *factory, t_list **words,
						struct s_build_context *context);
char				*factory_find_path(t_factory *factory, char *bin);
char				*factory_check_path(char *path, char *name);

int					factory_command_set_pipe(t_list **words,
						struct s_build_context *context);
int					factory_command_set_semicolon(t_list **words,
						struct s_build_context *context);
int					factory_command_set_input(t_list **words,
						struct s_build_context *context);
int					factory_command_set_output(t_list **words,
						struct s_build_context *context, int to_end);
int					factory_command_set_argv(t_pword *word,
						struct s_build_context *context);

struct s_comm_pair	factory_get_com_pair(t_dlist *node);
int					factory_exec_set_out(struct s_comm_pair	pair);
int					factory_exec_set_in(struct s_comm_pair	pair);
int					factory_exec_command(t_dlist *node, t_minishell *shell);
int					factory_exec_buildin(struct s_comm_pair pair,
						t_minishell *shell);
int					factory_exec_bin(struct s_comm_pair	pair,
						t_minishell *shell);

#endif
