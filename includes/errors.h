/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:03:00 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:31:36 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include "libft.h"
# include "exit_code.h"

# define _ERR_TITLE "minishell: "
# define _ERR_MULTL "multiline is not supported"
# define _ERR_UNKNOWN "something wrong..."
# define _ERR_NOTTERM "not a terminal"
# define _ERR_NOTTERMENV "environment variable TERM not set"
# define _ERR_NOTTERMTYPE "terminal type is not defined"
# define _ERR_UNTOKEN_BEGIN "syntax error near unexpected token `"
# define _ERR_UNTOKEN_END "\'"
# define _ERR_NOFILE "no such file or directory"
# define _ERR_NOCOMMAND "command not found"
# define _ERR_ISDIR "is a directory"
# define _ERR_PERMDEN "Permission denied"

int	err_cd_print(char *messege, int return_status, int exit_code, char *arg);
int	err_print(char *messege, int return_status, int exit_code);
int	err_print_untoken(char *token, int status);
int	err_print_nofile(char *file, int status);
int	err_print_object(char *object, char *messege, int exit_code, int status);

#endif
