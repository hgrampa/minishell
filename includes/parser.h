/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:35:39 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:29:44 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include "libft.h"
# include "environment.h"
# include "sbuffer.h"
# include "pword.h"

# define _PRS_DELIMITERS " \t"
# define _PRS_CONTROLERS ";|<>"
# define _PRS_ESC_WQUOTES_CAHRS "\"$`"
# define _PRS_QUOTES "\"\'"
# define _PRS_BUFFSIZE 40

struct						s_pcontext;

typedef struct s_minishell	t_minishell;

typedef int					(*t_state_body)(char**, struct s_pcontext*);

struct s_pcontext
{
	t_state_body		previous_state;
	t_state_body		current_state;
	t_stack				*state_stack;
	t_sbuffer			*buffer;
	enum e_pword_type	buffer_type;
	t_list				*words;
	t_env				*env;
	unsigned char		process :1;
	unsigned char		error :1;
};

int				parse_line(t_minishell *shell, char *line, t_list **words);

int				pcontext_set_state(struct s_pcontext *context,
					t_state_body next_state);
int				pcontext_return_state(struct s_pcontext *context);
t_state_body	pcontext_previous_state(struct s_pcontext *context);
int				pcontext_end_process(struct s_pcontext *context, int status);
int				pcontext_error(struct s_pcontext *context, int status);

int				pstate_core(char **line, struct s_pcontext *context);
int				pstate_squotes(char **line, struct s_pcontext *context);
int				pstate_wquotes(char **line, struct s_pcontext *context);
int				pstate_env(char **line, struct s_pcontext *context);
int				pstate_esc(char **line, struct s_pcontext *context);
int				pstate_cntrl(char **line, struct s_pcontext *context);

int				pbuffer_add_char(struct s_pcontext *context, char c);
int				pbuffer_add_str(struct s_pcontext *context, char *str);
int				pbuffer_open(struct s_pcontext *context,
					enum e_pword_type type);
int				pbuffer_close(struct s_pcontext *context);

#endif
