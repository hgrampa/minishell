/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:54:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/19 20:41:40 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_file.h"
#include  <fcntl.h>

int	serialize_history(t_dlist *root)
{
	
}

t_dlist	*deserialize_history(void)
{
	
}

// int main()
// {
// 	t_dlist *history;

// 	history = deserialize_history();
// 	printf("%s\n", history->data);
// 	printf("%s\n", history->next->data);
// 	printf("%s\n", history->next->next->data);	
// 	// history = history->next->next;
// 	// printf("%s\n", history->data);
// 	// printf("%s\n", history->previous->data);
// 	// printf("%s\n", history->previous->previous->data);
// 	// // t_dlist *test0;
// 	// t_dlist *test1;
// 	// t_dlist *test2;
// 	// test2 = ft_dlist_new("789 rwertertwertwerter4tw6er54t6wt4w6er5t");
// 	// test1 = ft_dlist_new("456");
// 	// test0 = ft_dlist_new("123 test");
// 	// ft_dlist_pull(&test1, test0);
// 	// ft_dlist_pull(&test2, test1);
// 	// serialize_history(test0);
// 	// printf("%s\n", test0->next->data);
// 	// printf("%s\n", test2->previous->data);
// 	// printf("%s\n", test1->previous->data);
// 	// printf("%s\n", test0->data);
// 	ft_dlist_free(&history, NULL);
// 	return(0);
// }
