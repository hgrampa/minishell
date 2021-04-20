/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:28:16 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/20 11:16:26 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_minishell	*minishell_create(const char *title, const char **envp)
{
	t_minishell *shell;

	shell = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
	if (shell == NULL)
		return (NULL);
	shell->title = ft_strdup(title);
	shell->env = env_create(envp);
	shell->input = input_create();
	shell->history = history_create();
	if (shell->title == NULL || shell->env == NULL || shell->input == NULL
		|| shell->history == NULL)
	{
		minishell_destroy(shell);
		return (NULL);
	}
	return (shell);
}

int			minishell_on_exit(t_minishell *shell)
{
	history_serealize(shell->history);
	return (1);
}

int			minishell_destroy(t_minishell *shell)
{
	if (shell->title != NULL)
		free(shell->title);
	if (shell->env != NULL)
		env_destroy(shell->env);
	if (shell->input != NULL)
		input_destroy(shell->input);
	if (shell->history != NULL)
		history_destroy(shell->history);
	free(shell);
	return (1);
}

int			minishell_init(t_minishell *shell)
{
	if (!term_init(shell->input->term)) // TODO пусть инпут сам занимается инициацияей
		return (0);
	if (!history_init(shell->history))
		return (0);
	shell->rand_next = 20;
	return (1);
}

static unsigned char	ft_rand(t_minishell *shell)
{
	shell->rand_next = shell->rand_next * 1103515245;
	return((unsigned char)(shell->rand_next / 65536) * 2768);
}

static void				mini_ctoa(char *str, unsigned char num)
{
	int		i;

	i = 3;
	while (i > 0)
	{
		str[--i] = (num % 10) + '0';
		num /= 10;
	}
}

int						minishell_write_title(t_minishell *shell)
{
	int				i;
	char			color[4];
	char			*title;
	unsigned char	num;

	i = -1;
	ft_bzero(color, 4 * sizeof(char));
	title = shell->title;
	num = ft_rand(shell) % 230 + 1;
	while (*title != '\0')
	{
		num = (num + 1) % 230;
		if (num == 16 || num == 0)
			num = 17;
		mini_ctoa(color, num);
		ft_putstr_fd("\e[38;5;", 1);
		ft_putstr_fd(color, 1);
		ft_putchar_fd('m', 1);
		ft_putchar_fd(*title, 1);
		title++;
	}
	ft_putstr_fd("\e[39m: ", 1);
	return (1);
}
