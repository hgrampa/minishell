/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbuffer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:16:15 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/21 12:12:33 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SBUFFER_H
# define SBUFFER_H

# include "libft.h"

/*
**	Contains a buffered string and it's data
**
**		- str - buffered string (null terminated)
**		- len - real len of buffered string
**		- size - real size of buffered string array
**		- step - multiplicity of buffered string array
**			!!! CAN NOT BE 0
**			realloc are used by this value
*/
typedef struct s_sbuffer
{
	char	*str;
	size_t	len;
	size_t	size;
	size_t	step;
}				t_sbuffer;

/*
**	Creates an instance of t_sbuffer
**
**		- Malloc and initializes buffered string by "step" value whith '\0'
**		- step CAN NOT BE 0 !!!
**		- In case of failure - returns NULL
*/
t_sbuffer	*sbuffer_create(size_t step);

/*
**	Free t_sbuffer instance and buffered string
**
**		- In case of an error, returns 0, otherwise 1
*/
int			sbuffer_destroy(t_sbuffer *buffer);

/*
**	Add string to the end of buffered string
**
** 		- If str len + buffer len >= buffer.size - realloc by step value
**		- In case of malloc error - return 0 (old buffer.str not freed)
*/
int			sbuffer_add_str(t_sbuffer *buffer, char *str);

/*
**	Add char to the end of buffered string
**
** 		- If buffer len + 1 >= buffer.size - realloc by step value
**		- In case of malloc error - return 0 (old buffer.str not freed)
*/
int			sbuffer_add_char(t_sbuffer *buffer, char c);

/*
**	Reset all char in buffered string at '\0', keeping the current size
** 
**		- set buffer.len to 0
**		- does not affect size of allocated memory
**		- In case of an error, returns 0, otherwise 1
*/
int			sbuffer_clear(t_sbuffer *buffer);

/*
**	Cleare last one char in buffered string
**
**		- reduces buffer.len by 1
**		- does not affect size of allocated memory
*/
int			sbuffer_backspace(t_sbuffer *buffer);

#endif
