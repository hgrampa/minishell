/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:33:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/24 23:22:15 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_command *command_create(char *name)
{
	t_command *command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	command->name = name;
	command->input = -1;
	command->output = -1;
	return (command);
}

int	command_destroy(t_command *command)
{
	if (command->argv != NULL)
		ft_list_free(command->argv, NULL); // TODO вроде строка - инстанция слов
	free(command);
	return (0);
}

void	command_set_buildin(t_command *command, int (*buildin)(t_list))
{
	command->is_buildin = 1;
	command->buildin = buildin;
}
