/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_factory.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:24:23 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 21:17:01 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COM_FACTORY_H
# define COM_FACTORY_H

# include "libft.h"
# include "pword.h"
# include "minishell.h"

int	com_factory_run_line(t_list *words, t_minishell *shell);

#endif
