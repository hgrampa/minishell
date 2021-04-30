/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:33:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:53:52 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "utilities.h"

t_command	*command_create(char *name)
{
	t_command	*command;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	if (name != NULL)
		command->name = ft_strdup(name);
	command->input = -1;
	command->output = -1;
	command->pid = -1;
	return (command);
}

int	command_destroy(t_command *command)
{
	if (command->argv != NULL)
		free_array(command->argv);
	if (command->name != NULL)
		free(command->name);
	free(command);
	return (1);
}

void	command_list_destroy(void *data)
{
	command_destroy((t_command *)data);
}

void	command_set_buildin(t_command *command, t_buildin buildin)
{
	command->is_buildin = 1;
	command->buildin = buildin;
}

void	command_print_argv(void *data)
{
	char	*argv;

	argv = (char *)data;
	printf("\t\t%s,\n", argv);
}
