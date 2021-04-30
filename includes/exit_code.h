/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:02:19 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 12:30:14 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_CODE_H
# define EXIT_CODE_H

# include "libft.h"

void	exit_code_set(int code);
void	exit_code_clamp_set(int code);
int		exit_code_peek(void);
int		exit_code_take(void);

#endif
