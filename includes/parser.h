/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:35:39 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/15 23:23:02 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include "libft.h"

# define _PRS_DELIMITERS " \t"
# define _PRS_CONTROLERS ";|<>"
# define _PRS_QUOTES "\"\'"
# define _PRS_BUFFSIZE 32

enum e_pword_type
{
	EWT_WORD,
	EWT_PIPE,
	EWT_SEMICOLON,
	EWT_REDIRECT1,
	EWT_REDIRECT2,
	EWT_REDIRECT3,
};

struct	s_buffer
{
	char	*str;
	int		last;
};

struct s_pcontext;

typedef int (*t_state_body)(char**, t_list**, struct s_pcontext*);

struct s_pcontext
{
	// t_state_body		previous_state;
	t_state_body		current_state;
	t_stack				*state_stack;
	char				*buffer;
	t_list				*words;
	char				process:1;
};

typedef struct	s_pword
{
	char				*value;
	enum e_pword_type	type;
}				t_pword;


int		parse_line(char *line, t_list **words);

int		core_state(char **line, t_list **words, struct s_pcontext *context);
int		squotes_state(char **line, t_list **words, struct s_pcontext *context);
int		wquotes_state(char **line, t_list **words, struct s_pcontext *context);
int		env_state(char **line, t_list **words, struct s_pcontext *context);
int		esc_state(char **line, t_list **words, struct s_pcontext *context);
int		cntrl_state(char **line, t_list **words, struct s_pcontext *context);

int		pbuffer_add_char(struct s_pcontext *context, char c); // если null то открывает
int		pbuffer_add_str(struct s_pcontext *context, char *str); // если null то открывает
int		pbuffer_open(struct s_pcontext *context);
int		pbuffer_close(struct s_pcontext *context);

#endif
