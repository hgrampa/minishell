/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 13:09:35 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/28 17:30:23 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			array[i++] = NULL;
		}
	}
	free(array);
}
