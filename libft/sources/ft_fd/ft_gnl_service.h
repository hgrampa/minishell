/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_service.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:25:53 by hgrampa           #+#    #+#             */
/*   Updated: 2020/12/28 14:32:20 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GNL_SERVICE_H
# define FT_GNL_SERVICE_H

# include "libft.h"

typedef struct s_cash
{
	char	*str;
	int		len;
	int		next;
}				t_cash;

int				cash_has_next_line(t_cash *cash);
int				cash_realloc(t_cash *cash, int new_len, int offset);
int				cash_read(t_cash **cash, int fd, int size);
int				cash_set_next_line(t_cash *cash, char **str);

int				clear_data(t_cash **cash, char **str1, int result);

#endif
