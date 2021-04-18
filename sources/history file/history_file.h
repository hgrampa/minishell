/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:54:11 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/18 15:54:14 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_FILE_H
# define HISTORY_FILE_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "environment.h"
# include "dlists.h"
# include <stdio.h>

int		serialize_history(t_dlist *root);
t_dlist	*deserialize_history(void);

#endif
