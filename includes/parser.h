/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:35:39 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/16 16:03:03 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include "libft.h"
# include "environment.h"

# define _PRS_DELIMITERS " \t"
# define _PRS_CONTROLERS ";|<>"
# define _PRS_QUOTES "\"\'"
# define _PRS_BUFFSIZE 32

// TODO текущая стадия - полем
// TODO буфер-почеловечески
// TODO \ символ

enum e_pword_type
{
	EWT_UNKNOWN = -1,
	EWT_WORD,
	EWT_PIPE,
	EWT_SEMICOLON,
	EWT_REDIRECT1, // <
	EWT_REDIRECT2, // >
	EWT_REDIRECT3, // >>
};

struct	s_buffer
{
	char	*str;
	int		last;
};

typedef struct s_pword
{
	char				*value;
	enum e_pword_type	type;
}				t_pword;


struct s_pcontext;
typedef int (*t_state_body)(char**, t_list**, struct s_pcontext*);

struct s_pcontext
{
	t_state_body		previous_state;
	t_state_body		current_state;
	t_stack				*state_stack;
	char				*buffer;
	enum e_pword_type	buffer_type;
	t_list				*words;
	t_env				*env;
	char				process:1;
};



int				parse_line(t_env *env, char *line, t_list **words);

void			pcontext_set_state(struct s_pcontext *context, t_state_body next_state);
void			pcontext_return_state(struct s_pcontext *context);
t_state_body	pcontext_previous_state(struct s_pcontext *context);
void			pcontext_end_process(struct s_pcontext *context);

int				core_state(char **line, t_list **words, struct s_pcontext *context);
int				squotes_state(char **line, t_list **words, struct s_pcontext *context);
int				wquotes_state(char **line, t_list **words, struct s_pcontext *context);
int				env_state(char **line, t_list **words, struct s_pcontext *context);
int				esc_state(char **line, t_list **words, struct s_pcontext *context);
int				cntrl_state(char **line, t_list **words, struct s_pcontext *context);

int				pbuffer_add_char(struct s_pcontext *context, char c);
int				pbuffer_add_str(struct s_pcontext *context, char *str);
int				pbuffer_open(struct s_pcontext *context, enum e_pword_type type);
int				pbuffer_close(struct s_pcontext *context); 

#endif
