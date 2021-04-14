/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 14:35:39 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/14 19:36:46 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include "libft.h"

# define _PRS_DELIMITERS " \t"
# define _PRS_CONTROLERS ";|<>"
# define _PRS_BUFFSIZE 32

enum e_parser_st
{
	EPS_CORE,
	EPS_STRQT,
	EPS_WKQT,
	EPS_ENV,
	EPS_ESC,
};

typedef int (*t_state_body)(char**, t_list**, struct s_pcontext*);

typedef struct s_pcontext
{
	// t_state_body		previous_state;
	t_state_body		current_state;
	t_stack				*state_stack;
	char				*buffer;
	t_list				*words;
	char				process:1;

};



int		core_state(char **line, t_list **words, struct s_pcontext *context);
int		squotes_state(char **line, t_list **words, struct s_pcontext *context);
int		wquotes_state(char **line, t_list **words, struct s_pcontext *context);
int		env_state(char **line, t_list **words, struct s_pcontext *context);
int		esc_state(char **line, t_list **words, struct s_pcontext *context);

int		pbuffer_add_char(struct s_pcontext *context, char c); // если null то открывает
int		pbuffer_add_str(struct s_pcontext *context, char *str); // если null то открывает
int		pbuffer_open(struct s_pcontext *context);
int		pbuffer_close(struct s_pcontext *context);



#endif
