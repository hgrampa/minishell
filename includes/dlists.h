/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_lists.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:39:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/17 18:39:09 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLISTS_H
# define DLISTS_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_dlist
{
	void			*data;
	struct s_dlist	*next;
	struct s_dlist	*previous;
}				t_dlist;

t_dlist				*ft_dlist_new(void *data);
void				ft_dlist_free(t_dlist **root, void (*del)(void*));
int					ft_dlist_pull(t_dlist **root, t_dlist *new_dlist);
void				ft_dlist_foreach(t_dlist *root, void (*f)(void *));
int					ft_dlist_add(t_dlist **root, void *data);

#endif