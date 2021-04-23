/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:03:00 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/23 12:48:45 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include "libft.h"

# define _ERR_TITLE "minishell: "
# define _ERR_MULTL "multiline is not supported"
# define _ERR_UNKNOWN "something wrong..."

int	err_fatal(char *messege, int status);
int	err_print(char *messege, int status);

#endif
