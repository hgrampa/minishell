/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbuffer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 11:16:31 by hgrampa           #+#    #+#             */
/*   Updated: 2021/04/21 00:28:16 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include "sbuffer.h"

static int	sbuffer_realloc(t_sbuffer *buffer, size_t rec_size)
{
	size_t	count;
	size_t	new_size;
	char	*ptr;
	
	count = rec_size / buffer->step + 1;
	new_size = buffer->step * count;
	ptr = buffer->str;
	buffer->str = (char *)ft_calloc(1, new_size);
	if (buffer->str == NULL)
		return (0);
	ft_memcpy(buffer->str, ptr, buffer->size);
	free(ptr);
	buffer->size = new_size;
	return (1);
}

t_sbuffer	*sbuffer_create(size_t step)
{
	t_sbuffer	*buffer;

	buffer = (t_sbuffer *)ft_calloc(1, sizeof(t_sbuffer));
	if (buffer == NULL)
		return (NULL);
	buffer->str = (char *)ft_calloc(step, sizeof(char));
	if (buffer->str == NULL)
	{
		free(buffer);
		return (NULL);
	}
	buffer->step = step;
	buffer->size = step;
	return (buffer);
}

int			sbuffer_destroy(t_sbuffer *buffer)
{
	if (buffer->str != NULL)
		free(buffer->str);
	free(buffer);
	return (1);
}

int			sbuffer_add_str(t_sbuffer *buffer, char *str)
{
	size_t	i;
	size_t	str_len;
	size_t	rec_size;
	char	*buff_end;

	str_len = ft_strlen(str);
	rec_size = (str_len + buffer->len) * sizeof(char);
	if (rec_size >= buffer->size)
	{
		if (!sbuffer_realloc(buffer, rec_size))
			return (0);
	}
	buff_end = &(buffer->str[buffer->len]);
	i = -1;
	while (++i < str_len)
		buff_end[i] = str[i];
	buffer->len += str_len;
	return (1);
}

int			sbuffer_add_char(t_sbuffer *buffer, char c)
{
	size_t	rec_size;
	char	*buff_end;

	rec_size = (buffer->len + 1) * sizeof(char);
	if (rec_size >= buffer->size)
	{
		if (!sbuffer_realloc(buffer, rec_size))
			return (0);
	}
	buff_end = &(buffer->str[buffer->len]);
	*buff_end = c; 
	buffer->len += 1;
	return (1);
}

int			sbuffer_clear(t_sbuffer *buffer)
{
	ft_bzero(buffer->str, buffer->size);
	buffer->len = 0;
	return (1);
}

int			sbuffer_backspace(t_sbuffer *buffer)
{
	if (buffer->len > 0)
	{
		buffer->str[buffer->len] = '\0';
		buffer->len--;
	}
	return (1);
}

// void	sbuffer_print(t_sbuffer *buffer)
// {
// 	printf("buffer:\n");
// 	printf("\tstr: \"%s\"\n", buffer->str);
// 	printf("\tlen: %lu\n", buffer->len);
// 	printf("\tsize: %lu\n", buffer->size);
// 	printf("\tstep: %lu\n", buffer->step);
// }

// int		buffer_has_next_line(t_sbuffer *buffer, int *index)
// {
// 	int i;
// 	char *str;
// 	//
// 	str = buffer->str;
// 	if (str == NULL)
// 		return (0);
// 	i = -1;
// 	while (str[++i] != '\0')
// 	{
// 		if (str[i] == '\n')
// 		{
// 			*index = i;
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// gcc -g -L ../libft/ -lft -I ../libft/includes -I ../includes sbuffer.c -o buffer  
// #define READ_BUFFSIZE 32
// #define S_BUFFSIZE_1 1
// #define S_BUFFSIZE_2 256

// int main(int argc, char const *argv[])
// {
// 	t_sbuffer	*buffer;
// 	int			next_i;
// 	char		read_buff;
// 	ssize_t		read_len;
// 
// 	// while (21)
// 	// {
// 		buffer = sbuffer_create(S_BUFFSIZE);
// 		if (buffer == NULL)
// 		{
// 			perror("");
// 			exit(1);
// 		}
// 		while (!buffer_has_next_line(buffer, &next_i))
// 		{
// 			read_len = read(0, &read_buff, 1);
// 			if (read_len == -1)
// 				exit (1);
// 			if (!sbuffer_add_char(buffer, read_buff))
// 			{
// 				perror("");
// 				exit(1);
// 			}
// 			ft_putchar_fd(read_buff, 1);
// 		}
// 		sbuffer_print(buffer);
// 		sbuffer_destroy(buffer);
// 	// }
// 	return 0;
// }

// int main(int argc, char const *argv[])
// {
// 	t_sbuffer	*buffer1;
// 	t_sbuffer	*buffer2;
// 	int			next_i;
// 	char		read_buff[READ_BUFFSIZE + 1];
// 	ssize_t		read_len;
// 	// 
// 	// while (21)
// 	// {
// 		buffer1 = sbuffer_create(S_BUFFSIZE_1);
// 		buffer2 = sbuffer_create(S_BUFFSIZE_2);
// 		if (buffer1 == NULL)
// 		{
// 			perror("");
// 			exit(1);
// 		}
// 		while (!buffer_has_next_line(buffer1, &next_i))
// 		{
// 			ft_bzero(read_buff, (READ_BUFFSIZE + 1) * sizeof(char));
// 			read_len = read(0, read_buff, READ_BUFFSIZE);
// 			if (read_len == -1)
// 				exit (1);
// 			if (!sbuffer_add_str(buffer1, read_buff))
// 			{
// 				perror("");
// 				exit(1);
// 			}
// 			if (!sbuffer_add_str(buffer2, read_buff))
// 			{
// 				perror("");
// 				exit(1);
// 			}
// 			ft_putstr_fd(read_buff, 1);
// 		}
// 		sbuffer_print(buffer1);
// 		sbuffer_destroy(buffer1);
// 		sbuffer_print(buffer2);
// 		sbuffer_destroy(buffer2);
// 	// }
// 	return 0;
// }

