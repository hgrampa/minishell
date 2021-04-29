/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:14:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 17:23:41 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildin.h"

t_buildin	buildin_find(char *name)
{
	if (ft_strcmp(name, _BUILDIN_CD) == 0)
		return (buildin_cd);
	else if (ft_strcmp(name, _BUILDIN_ECHO) == 0)
		return (buildin_echo);
	else if (ft_strcmp(name, _BUILDIN_ENV) == 0)
		return (buildin_env);
	else if (ft_strcmp(name, _BUILDIN_EXIT) == 0)
		return (buildin_exit);
	else if (ft_strcmp(name, _BUILDIN_EXPORT) == 0)
		return (buildin_export);
	else if (ft_strcmp(name, _BUILDIN_PWD) == 0)
		return (buildin_pwd);
	else if (ft_strcmp(name, _BUILDIN_UNSET) == 0)
		return (buildin_unset);
	else
		return (NULL);
}
