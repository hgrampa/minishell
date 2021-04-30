/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_build_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:04:18 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/30 14:38:08 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"

static int	factory_command_set_redirect(enum e_pword_type type, t_list **words,
	struct s_build_context *context)
{
	if (type == EWT_REDIR_IN)
	{
		if (!factory_command_set_input(words, context))
			return (0);
	}
	else if (type == EWT_REDIR_OUT)
	{
		if (!factory_command_set_output(words, context, 0))
			return (0);
	}
	else if (type == EWT_REDIR_APPEND)
	{
		if (!factory_command_set_output(words, context, 1))
			return (0);
	}
	return (1);
}

static int	factory_build_command_param(t_list **words,
	struct s_build_context *context)
{
	t_pword		*word;

	while (*words != NULL)
	{
		word = (t_pword *)(*words)->data;
		if (word->type == EWT_PIPE)
			return (factory_command_set_pipe(words, context));
		else if (word->type == EWT_SEMICOLON)
			return (factory_command_set_semicolon(words, context));
		else if (factory_is_redirection(word->type))
		{
			if (!factory_command_set_redirect(word->type, words, context))
				return (0);
		}
		else
		{
			if (context->command->name == NULL)
				return (1);
			if (!factory_command_set_argv(word, context))
				return (0);
		}	
		*words = (*words)->next;
	}
	context->process = 0;
	return (1);
}

t_command	*factory_command_finde(t_factory *factory, t_command *command,
	char *name, struct s_build_context *context)
{
	t_buildin	buildin;

	buildin = buildin_find(name);
	if (buildin != NULL)
		command_set_buildin(command, buildin);
	else
	{
		free(command->name);
		command->name = factory_find_path(factory, name);
		if (command->name == NULL)
		{
			command_destroy(command);
			return (NULL);
		}
	}
	if (!ft_list_add(&context->argl, command->name))
	{
		command_destroy(command);
		return (NULL);
	}
	return (command);
}

static t_command	*factory_command_create(t_factory *factory, char *name,
	struct s_build_context *context)
{
	t_command	*command;

	command = command_create(name);
	if (command == NULL)
		return (NULL);
	return (factory_command_finde(factory, command, name, context));
}

int	factory_biuld_command(t_factory *factory, t_list **words,
	struct s_build_context *con)
{
	t_pword		*word;

	if (*words == NULL)
	{
		con->process = 0;
		return (1);
	}
	word = (t_pword *)(*words)->data;
	if (word->type == EWT_WORD)
	{
		con->command = factory_command_create(factory, word->value, con);
		*words = (*words)->next;
	}
	else if (word->type == EWT_REDIR_IN || word->type == EWT_REDIR_OUT
		|| word->type == EWT_REDIR_APPEND)
		con->command = command_create(NULL);
	else
		return (err_print_untoken(word->value, 0));
	if (con->command == NULL)
		return (0);
	return (factory_build_command_param(words, con));
}
