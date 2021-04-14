/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:24:53 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/10 13:20:01 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "libft.h"

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

int get_value_from_key(t_pair *pair, char const *key);
int create_represent(t_env *environment, int ln);
t_pair	*env_get_pair(t_env *env, char const *key);
t_pair	*create_pair_from_str(char const *str);
t_pair	*create_new_pair(char const *key, char const *value);
void	print_represent(char **array);
void	print_list(t_list *lst);
void	free_pair(void *ptr);
void	free_array(char **array);
void	ft_list_sort(t_list *elem);


#endif
