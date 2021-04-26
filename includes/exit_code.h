/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 12:02:19 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/26 20:25:05 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_CODE_H
# define EXIT_CODE_H

void	exit_code_set(int code);
void	exit_code_clamp_set(int code);
int		exit_code_get(void);

#endif
