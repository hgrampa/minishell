/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:00:48 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 22:22:22 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"

// TODO "yes | head" ломает сигналы

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
			if (!factory_command_set_argv(word, context))
				return (0);
		}	
		*words = (*words)->next;
	}
	context->process = 0;
	return (1);
}

t_command	*factory_command_create(t_factory *factory, char *name,
	struct s_build_context *context)
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
	if (!ft_list_add(&context->argl, command->name)) // ссылку а не инстанцию
	{
		command_destroy(command);
		return (NULL);
	}
	return (command);
}

int	factory_biuld_command(t_factory *factory, t_list **words,
	struct s_build_context *context)
{
	t_pword		*word;

	if (*words == NULL)
	{
		context->process = 0;
		return (1);
	}
	word = (t_pword *)(*words)->data;
	if (word->type == EWT_WORD)
	{
		context->command = factory_command_create(factory, word->value, context);
		*words = (*words)->next;
	}
	else if (word->type == EWT_REDIRECT1 || word->type == EWT_REDIRECT2 || word->type == EWT_REDIRECT3)
		context->command = command_create(NULL);
	else
		return (err_print_untoken(word->value, 0));
	if (context->command == NULL)
		return (0);
	return (factory_build_command_param(factory, words, context));
}

int factory_build_commands(t_factory *factory, t_list *words, t_minishell *shell)
{
	int						result;
	struct s_build_context	context;

	context.process = 1;
	while (context.process)
	{
		context.argl = NULL;
		context.command = NULL;
		result = factory_biuld_command(factory, &words, &context);
		if (result == 0)
			return (0);
		if (context.command == NULL)
			continue ;
		context.command->argv = ft_list_tosa(context.argl); // TODO проверочку на ошибку бы
		if (context.argl != NULL)
			ft_list_free(&context.argl, NULL);	
		ft_dlist_add(&factory->commands, context.command);
	}
	return (1);
}
