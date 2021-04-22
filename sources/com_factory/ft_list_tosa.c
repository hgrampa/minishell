/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_tosa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 18:23:10 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/22 14:28:46 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static char	**clear(char **array)
{
	while (*array != NULL)
	{
		free(*array);
		array++;
	}
	free(array);
	return (NULL);
}

char		**ft_list_tosa(t_list *list)
{
	size_t	i;
	size_t	count;
	char	**array;

	count = ft_list_count(list);
	array = (char **)ft_calloc(count + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		array[i] = ft_strdup((char *)list->data);
		if (array == NULL)
			return (clear(array));
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

int main(int argc, char const *argv[])
{
	int		i;
	t_list	*list;
	char	**new_arg;
	
	if (argc > 1)
	{
		i = 0;
		while (++i < argc)
			ft_list_add(&list, argv[i]);

		new_arg = ft_list_tosa(list);
		if (new_arg == NULL)
			return (0); // TODO возврат ошибки
		ft_list_free(list, free);

		i = -1;
		while (new_arg[++i] != NULL)
		{
			printf("\"%s\"-[%i]\n", new_arg[i], i);
		}

	}

	return 0;
}

// gcc -g ft_list_tosa.c -L ../../libft -lft -I ../../libft/includes -o ltosa


// int	args_create(char **args, size_t len)
// {
	
// }

// int args_add(char **args, char *str)
// {
	
// }

// int args_destroy(char **args)
// {
// 	if (args != NULL)
// 	{
// 		while ()
// 		{
			
// 		}
// 		free(args);
// 	}
// 	return (1);
// }
