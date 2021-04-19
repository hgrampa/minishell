/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssentine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:54:03 by ssentine          #+#    #+#             */
/*   Updated: 2021/04/18 15:54:07 by ssentine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_file.h"
#include  <fcntl.h>

int	serialize_history(t_dlist *root)
{
	int		fd;

	fd = open("history.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd)
	{
		while (root != NULL)
		{
			write(fd, root->data, ft_strlen(root->data));
			write(fd, "\n", 1);
			root = root->next;
		}
	}
	else
		return (0);
	close(fd);
	return (1);
}

t_dlist	*deserialize_history(void)
{
	int		fd;
	int		result;
	char	*line;
	t_dlist	*history;

	history = NULL;
	fd = open("history.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Fail to open the history file\n");
		return (NULL);
	}
	line = NULL;
	result = ft_gnl(fd, &line, 32);
	while (result > 0)
	{
		ft_dlist_add(&history, ft_strdup(line));
		free(line);
		result = ft_gnl(fd, &line, 32);
	}
	ft_dlist_add(&history, ft_strdup(line));
	free(line);
	close(fd);
	return (history);
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
