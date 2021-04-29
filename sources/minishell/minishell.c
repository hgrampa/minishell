/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:28:16 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 15:52:54 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errors.h"

t_minishell	*minishell_create(const char *title, const char **envp)
{
	t_minishell	*shell;

	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
	if (shell == NULL)
		return (NULL);
	shell->title = ft_strdup(title);
	shell->env = env_create(envp);
	shell->input = input_create();
	shell->history = history_create();
	shell->factory = factory_create();
	if (shell->title == NULL || shell->env == NULL || shell->input == NULL
		|| shell->history == NULL || shell->factory == NULL)
	{
		err_print(NULL, 0, 1);
		minishell_destroy(shell);
		return (NULL);
	}
	return (shell);
}

void	minishell_exit(t_minishell *shell, int status)
{
	if (shell->history != NULL)
		history_serealize(shell->history);
	minishell_destroy(shell);
	exit(status);
}

int	minishell_destroy(t_minishell *shell)
{
	if (shell->title != NULL)
		free(shell->title);
	if (shell->env != NULL)
		env_destroy(shell->env);
	if (shell->input != NULL)
		input_destroy(shell->input);
	if (shell->history != NULL)
		history_destroy(shell->history);
	if (shell->factory != NULL)
		factory_destroy(shell->factory);
	free(shell);
	return (1);
}

int	minishell_at_newline(t_minishell *shell)
{
	shell->line = NULL;
	if (shell->words != NULL)
	{
		ft_list_free(&shell->words, pword_destroy);
		shell->words = NULL;
	}
	minishell_write_title(shell);
	return (1);
}

int	minishell_init(t_minishell *shell)
{
	signal(SIGINT, minishell_signal_int);
	signal(SIGQUIT, minishell_signal_quit);
	if (!input_init())
		return (0);
	if (!history_init(shell->history))
		return (0);
	shell->process = 1;
	shell->rand_next = 20;
	return (1);
}
