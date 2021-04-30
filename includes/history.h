/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 20:52:46 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:25:17 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

# define _HISTORY_FILE_NAME ".mini_history"
# define _HISTORY_READ_BUFF_SIZE 80

typedef struct s_history
{
	t_dlist	*root;
	t_dlist	*carriage;
}	t_history;

t_history	*history_create(void);
int			history_init(t_history *history);
int			history_destroy(t_history *history);
int			history_serealize(t_history *history);
int			history_deserealize(t_history *history);
int			history_add(t_history *history, char *str);
char		*history_up(t_history *history);
char		*history_down(t_history *history);

#endif
