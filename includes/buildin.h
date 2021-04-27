/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:13:48 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/27 15:10:05 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDIN_H
# define BUILDIN_H

# include "libft.h"

# define _BUILDIN_CD "cd"
# define _BUILDIN_ECHO "echo"
# define _BUILDIN_ENV "env"
# define _BUILDIN_EXIT "exit"
# define _BUILDIN_EXPORT "export"
# define _BUILDIN_PWD "pwd"
# define _BUILDIN_UNSET "unset"

typedef struct s_minishell	t_minishell;
typedef int					(*t_buildin)(char**, t_minishell*);

t_buildin	buildin_find(char *name);

int			buildin_cd(char **argv, t_minishell *shell);
int			buildin_echo(char **argv, t_minishell *shell);
int			buildin_env(char **argv, t_minishell *shell);
int			buildin_exit(char **argv, t_minishell *shell);
int			buildin_export(char **argv, t_minishell *shell);
int			buildin_pwd(char **argv, t_minishell *shell);
int			buildin_unset(char **argv, t_minishell *shell);

void		print_export_list(t_list *collection);
int			check_invalid_key(char *key);
int			check_for_plus(char *str);

#endif
