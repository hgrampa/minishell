/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:13:48 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/24 22:35:10 by hgrampa          ###   ########.fr       */
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
typedef int					(*t_buildin)(t_list);

t_buildin	buildin_find(char *name);

int			buildin_cd (t_list *argv, t_minishell *shell);
int			buildin_echo(t_list *argv, t_minishell *shell);
int			buildin_env(t_list *argv, t_minishell *shell);
int			buildin_exit(t_list *argv, t_minishell *shell);
int			buildin_export(t_list *argv, t_minishell *shell);
int			buildin_pwd(t_list *argv, t_minishell *shell);
int			buildin_unset(t_list *argv, t_minishell *shell);

#endif
