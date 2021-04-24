/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:14:31 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/24 21:25:56 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "factory.h"


int	build_command_argv(t_factory *factory, t_list **words, struct s_build_context *context)
{
	t_pword		*word;

	while (*words != NULL)
	{
		word = (t_pword *)(*words)->data;
		if (word->type == EWT_PIPE)
		{
			*words = (*words)->next;
			context->command->is_pipe = 1;
			return (1);
		}
		else if (word->type == EWT_SEMICOLON)
		{
			*words = (*words)->next;
			return (1);
		}
		else if (word->type == EWT_REDIRECT1)
		{
			int fd;
			// t_pword *next_word;

			// next_word = (t_pword *)words->next->data;
			// if (next_word == NULL)
			// 	return (0); // TODO syntax error near unexpected token `newline'
			// fd = open(next_word->value, 1)
			if (context->command->in_fd != -1)
				close(context->command->in_fd);
			if (fd == -1)
				return (0); // word->value: No such file or directory
			context->command->in_fd = fd;
			return (1);
		}
		else if (word->type == EWT_REDIRECT2)
		{
			int fd;

		}
		else if (word->type == EWT_REDIRECT3)
		{
		}
		else
			ft_list_add(context->command->argv, word->value); // TODO проверку на ошибку
		
		*words = (*words)->next;
	}
	return (0);
}

int	biuld_command(t_factory *factory, t_list **words, struct s_build_context *context)
{
	t_command	*command;
	t_pword		*word;

	command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (command == NULL)
		return (0);
	command->in_fd = -1;
	command->out_fd = -1;
	word = (t_pword *)(*words)->data;
	// TODO может начинаться с ридеректов
	if (word->type != EWT_WORD)
		return (0); // TODO syntax error near unexpected token `word->value'
	// TODO сначала проверить что это не buildin
	command->path = factory_find_path(factory, word->value);
	if (context->command->path == NULL)
	{
		free(command);
		return (0); // TODO word->value: No such file or directory
	}
	context->command = command;
	*words = (*words)->next;
	return (biuld_command_argv(factory, words, context));
}

int factory_build_commands(t_factory *factory, t_list *words, t_minishell *shell)
{
	int						result;
	struct s_build_context	context;

	context.command = NULL;
	context.process = 1;
	while (context.process)
	{
		result = biuld_command(factory, &words, &context);
		if (result == 0)
			return (0);
		// if (context.command != NULL)
		ft_dlist_add(factory->commands, context.command);
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
}

int	factory_run_line(t_list *words, t_minishell *shell)
{
	t_pword		*word;
	t_factory	factory;

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
