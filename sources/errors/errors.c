/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:32:22 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:31:56 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int	err_cd_print(char *messege, int return_status, int exit_code, char *arg)
{
	if (messege == NULL)
		messege = strerror(errno);
	ft_putstr_fd(_ERR_TITLE, STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(messege, STDERR_FILENO);
	exit_code_set(exit_code);
	return (return_status);
}

int	err_print(char *messege, int return_status, int exit_code)
{
	if (messege == NULL)
		messege = strerror(errno);
	ft_putstr_fd(_ERR_TITLE, STDERR_FILENO);
	ft_putendl_fd(messege, STDERR_FILENO);
	exit_code_set(exit_code);
	return (return_status);
}

int	err_print_untoken(char *token, int status)
{	
	ft_putstr_fd(_ERR_TITLE, STDERR_FILENO);
	ft_putstr_fd(_ERR_UNTOKEN_BEGIN, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd(_ERR_UNTOKEN_END, STDERR_FILENO);
	exit_code_set(258);
	return (status);
}

int	err_print_nofile(char *file, int status)
{	
	char	*messege;

	messege = strerror(errno);
	ft_putstr_fd(_ERR_TITLE, STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(messege, STDERR_FILENO);
	exit_code_set(1);
	return (status);
}

int	err_print_object(char *object, char *messege, int exit_code, int status)
{	
	ft_putstr_fd(_ERR_TITLE, STDERR_FILENO);
	ft_putstr_fd(object, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (messege == NULL)
		messege = strerror(errno);
	ft_putendl_fd(messege, STDERR_FILENO);
	exit_code_set(exit_code);
	return (status);
}
