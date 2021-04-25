/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 21:33:59 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/25 18:53:50 by hgrampa          ###   ########.fr       */
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
	char **argv;

	if (command->argv != NULL)
	{
		argv = command->argv;
		while ((*argv) != NULL)
			free((*argv)++);
		free(argv); // TODO проверить очисткуу
	}
	free(command);
	return (0);
}

void	command_set_buildin(t_command *command, t_buildin buildin)
{
	command->is_buildin = 1;
	command->buildin = buildin;
}

void	command_print_argv(void *data)
{
	char *argv;

	argv = (char *)data;
	printf("\t\t%s,\n", argv);
}

void command_print(void *data)
{
	t_command *command;

	command = (t_command *)data;
	printf("[\n\tname: %s,\n", command->name);
	printf("\targv:\n\t[\n");
	// ft_list_foreach(command->argl, command_print_argv);
	printf("\t]\n");
	printf("\tis_pipe: %d,\n", command->is_pipe);
	printf("\tis_buildin: %d,\n", command->is_buildin);
	printf("\tpipe: [%d,%d],\n", command->pipe[0], command->pipe[0]);
	printf("\tinput: %d,\n", command->input);
	printf("\toutput: %d,\n", command->output);
	printf("\tbuildin: %p,\n", command->buildin);
	printf("]\n");
}
