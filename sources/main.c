/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:54:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/28 18:16:59 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/signal.h>
#include "minishell.h"
#include "input.h"
#include "parser.h"
#include "environment.h"
#include "pword.h"
#include "factory.h"

// TODO
// //	снес PATH и перестали работать билдын env
// //	и перестали работать относительные пути (и мб абсолютные)

// // 	env после удаления всех переменных

// // export a=b; echo $a - не напечатал b (парсить только до ;) - фабрику в парсер

//	// echo asadads $test echo lsds - asadads ;echo lsds (test =";")
//		// echo asadads $test echo lsds - asadads ; echo lsds (пробел)

// //	exit 99999999999999999999999999999999999999999999999 - сега
// //		(bash: exit: 99999999999999999999999999999999999999999999999: numeric argument required)

// // 	exit 257 - сега

// //	buildins - поменять bash в предупреждениях

// Убрать pid из минишела

// // echo | echo - ломет каретку

// // редиректы с echo не работаю

// "yes | head" ломает сигналы (говорять нужно в самом конце exit сделать)

// коды возврата так и не работают (от вейтпида)

// >> foo.txt - не создает файл

//// при пайпе не работают сигналы

// // разыминовывание пустой переменной добавляет ли запись в историю (в теории строка пустая)

static int	process(t_minishell *shell)
{
	while (shell->process)
	{
		minishell_at_newline(shell);

		// TODO работаться уже с возвращаем значении
		if (!input_get_next_line(shell->input, &shell->line, shell))
			return (0); // TODO очистку при ошибках (вроде есть)
		if (shell->line == NULL)
			continue ;

		// Добавляю instance в историю
		if (!history_add(shell->history, shell->line))
		{
			free (shell->line);
			return (0); // TODO возврат ошибки
		}

		// Получаю слова от парсера
		if (!parse_line(shell, shell->line, &shell->words))
			return (1); // TODO возврат ошибки
	}
	return (1);
}

int		main(int argc, char const *argv[], char const *envp[])
{
	int			result;
	t_minishell	*shell;

	shell = minishell_create(_MINISHELL_TITLE, envp);
	if (shell == NULL)
		return (err_print(NULL, 1, 1));
	result = 0;
	if (minishell_init(shell))
	{
		if (!process(shell))
			result = 1;
	}
	else
		result = 1;
	minishell_exit(shell, result);
	argc = 0;
	argv = 0;
	return (0);
}
