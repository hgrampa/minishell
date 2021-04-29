/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:24:53 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/29 13:57:46 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"
# include "utilities.h"

# define _ENV_SHLVL "SHLVL"
# define _ENV_SHLVL_EMPY ""
# define _ENV_SHLVL_DEFAULT "1"

/*
**	Pair of key-value environment variable
*/
typedef struct s_pair
{
	char	*key;
	char	*value;
}				t_pair;

/*
**	Storage of environment variables and it string representation
**
**		- Collection contains type t_pair
**		- represent - null terminating array of strings
*/
typedef struct s_env
{
	t_list	*collection;
	void	*represent;
	char	*exit_code;
}				t_env;

/*
**	Creates an instance of t_env based on a string
**
**		- String of key value pair divided by sign '\n' in such format:
**			KEY_1=VALUE_1
**			KEY_2=VALUE_2
**		- In case of failure - returns NULL
*/
t_env	*env_create(char const *represent[]);

/*
**	Free all instance in t_env
**
**		-In case of an error, returns 0, otherwise 1 
*/
int		env_destroy(t_env *env);

/*
**	Updates the string representation of the collection
**
**		- In case of an error, returns 0, otherwise 1 
*/
int		env_update(t_env *env);

/*
**	Returns instance value of the environment variable by key
**
**		- If no such key - returns null
*/
char	*env_get_value(t_env *env, char const *key);

/*
**	Sets the value of a variable by key
**
**		- If such a key exists in the collections, update value
**		- Otherwise - creates a new 
**		- Updates the representation of the collection
**		- In case of an error, returns 0, otherwise 1 
*/
int		env_set(t_env *env, char const *key, char const *value);

/*
**	Unset the value of a variable by key
**
**		- Free memory of removable value
**		- Updates the representation of the collection
**		- In case of an error, returns 0, otherwise 1 
*/
int		env_unset(t_env *env, char const *key);

int		env_get_value_from_key(t_pair *pair, char const *key);
t_list	*env_get_previous_pair(t_env *env, char const *key);
t_pair	*env_get_pair(t_env *env, char const *key);
char	*env_get_exit_code(t_env *env);
t_pair	*env_pair_from_str(char const *str);
t_pair	*env_create_new_pair(char const *key, char const *value);
void	env_print_represent(char **array);
void	env_print_list(t_list *lst);
void	env_free_pair(void *ptr);
void	env_list_sort(t_list *elem);
void	env_increment_shlvl(t_env *env);
int		env_isname_char(char c);
t_pair	*env_create_new_pair(char const *key, char const *value);
int		env_create_represent(t_env *environment, int ln);
int		env_before_update(t_list *pair, t_env *env);
int		env_compare_pairs(t_list *elem_cmp, t_list *temp_elem);
char	*env_create_key_value_str(t_pair *pair);

#endif
