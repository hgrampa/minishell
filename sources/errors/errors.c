/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:32:22 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 19:37:54 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	err_fatal(char *messege, int status)
{
	if (messege == NULL)
		messege = strerror(errno); // TODO man strerror
	ft_putstr_fd(_ERR_TITLE, STDERR_FILENO);
	ft_putendl_fd(messege, STDERR_FILENO);
	return (status);
}

int	err_print(char *messege, int status)
{
	if (messege == NULL)
		messege = strerror(errno);
	ft_putstr_fd(_ERR_TITLE, STDERR_FILENO);
	ft_putendl_fd(messege, STDERR_FILENO);
	return (status);
}