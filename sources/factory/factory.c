/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:14:31 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/25 12:54:23 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"


// TODO переименовать
int	factory_build_command_param(t_factory *factory, t_list **words,
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
		else if (word->type == EWT_REDIRECT1)
		{
			if (!factory_command_set_input(words, context))
				return (0);
		}
		else if (word->type == EWT_REDIRECT2)
		{
			if (!factory_command_set_output(words, context, 0))
				return (0);
		}
		else if (word->type == EWT_REDIRECT3)
		{
			if (!factory_command_set_output(words, context, 1))
				return (0);
		}
		else
		{
			if (!factory_command_set_argv(word, context)) // 
				return (0);
		}	
		*words = (*words)->next;
	}
	context->process = 0;
	return (1);
}

t_command	*factory_command_create(t_factory *factory, char *name)
{
	t_command	*command;
	t_buildin	buildin;

	command = command_create(name);
	if (command == NULL)
		return (0);									
	buildin = buildin_find(name);
	if (buildin != NULL)
		command_set_buildin(command, buildin);
	else
	{
		command->name = factory_find_path(factory, name);
		if (command->name == NULL)
		{
			command_destroy(command);
			err_print_nofile(name, 0);
			return (NULL);
		}
	}
	return (command);
}

int	factory_biuld_command(t_factory *factory, t_list **words,
	struct s_build_context *context)
{
	t_pword		*word;

	word = (t_pword *)(*words)->data;
	if (word->type == EWT_WORD)
		context->command = factory_command_create(factory, word->value);
	// TODO Тут отработку ридеректа как первого слова
	else
		return (err_print_untoken(word->value, 0));
	if (context->command == NULL)
		return (0);
	*words = (*words)->next;
	return (factory_build_command_param(factory, words, context));
}

int factory_build_commands(t_factory *factory, t_list *words, t_minishell *shell)
{
	int						result;
	struct s_build_context	context;

	context.command = NULL;
	context.process = 1;
	while (context.process)
	{
		result = factory_biuld_command(factory, &words, &context);
		if (result == 0)
			return (0);
		// if (context.command != NULL)
		ft_dlist_add(&factory->commands, context.command);
	}
	
	return (1);
}

int	factory_init(t_factory *factory, t_minishell *shell)
{
	factory->env_path = env_get_value(shell->env, "PATH");
	if (factory->env_path != NULL)
		factory->paths = ft_split(factory->env_path, ':'); // не проверяю на ошибку
	else
		factory->paths = NULL;
	factory->commands = NULL;
	factory->result = 1;
	return (1);
}

int	factory_exec_commands(t_factory *factory, t_minishell *shell)
{
	ft_list_foreach((t_list *)factory->commands, command_print);
	return (1);
}

int	factory_run_line(t_list *words, t_minishell *shell)
{
	t_pword		*word;
	t_factory	factory;

	// factory_init(&factory, shell);
	if (!factory_init(&factory, shell))
		return (0);
	if (factory_build_commands(&factory, words, shell))
	{
		factory_exec_commands(&factory, shell);
	}
	factory_destroy(&factory);
	return (factory.result);
}

int	factory_destroy(t_factory *factory)
{
	if (factory->paths != NULL)
		free_array(factory->paths);
	return (1);
}
