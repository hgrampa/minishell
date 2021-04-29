/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 11:13:24 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 13:53:10 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "errors.h"

static int	term_is_key_muted(char *buff, ssize_t len)
{
	return (ft_strncmp(buff, key_right, len) == 0
		|| ft_strncmp(buff, key_left, len) == 0
		|| ft_strncmp(buff, key_ppage, len) == 0
		|| ft_strncmp(buff, key_npage, len) == 0
		|| ft_strncmp(buff, key_home, len) == 0
		|| ft_strncmp(buff, "\t", len) == 0
		|| ft_strncmp(buff, "\f", len) == 0
		|| ft_strncmp(buff, "\v", len) == 0
		|| ft_strncmp(buff, "\x1c", len) == 0
		|| *buff < 0
		|| ft_strncmp(buff, key_end, len) == 0);
}

enum e_key_type	term_key_type(char *buff, ssize_t len)
{
	if (ft_strncmp(buff, "\177", len) == 0)
		return (EKT_BACKSPACE);
	else if (term_is_key_muted(buff, len))
		return (EKT_MUTED);
	else if (ft_strncmp(buff, key_up, len) == 0
		|| ft_strncmp(buff, cursor_up, len) == 0
		|| ft_strncmp(buff, "\e[A", len) == 0)
		return (EKT_UPARR);
	else if (ft_strncmp(buff, key_down, len) == 0
		|| ft_strncmp(buff, column_address, len) == 0
		|| ft_strncmp(buff, "\e[B", len) == 0)
		return (EKT_DWARR);
	else if (ft_strncmp(buff, "\4", len) == 0)
		return (EKT_CNTRLD);
	else if (ft_strncmp(buff, "\3", len) == 0)
		return (EKT_CNTRLC);
	else
		return (EKT_NOTKEY);
}
