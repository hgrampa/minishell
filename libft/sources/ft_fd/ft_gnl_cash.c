/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_cash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 18:30:20 by hgrampa           #+#    #+#             */
/*   Updated: 2021/01/23 11:21:38 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl_service.h"

int	cash_has_next_line(t_cash *cash)
{
	int		i;
	char	*str;

	if (!cash->str)
	{
		cash->next = -1;
		return (0);
	}
	i = 0;
	str = cash->str;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			cash->next = i;
			return (1);
		}
		i++;
	}
	cash->next = -1;
	return (0);
}

int	cash_realloc(t_cash *cash, int new_len, int offset)
{
	char	*new_str;

	new_str = NULL;
	if (new_len > 0)
	{
		new_str = (char *)ft_calloc(new_len + 1, sizeof(char));
		if (new_str == NULL)
			return (0);
		if (cash->str != NULL)
		{
			ft_strncat(new_str, &(cash->str[offset]), cash->len - offset);
			free(cash->str);
		}
		cash->str = new_str;
	}
	else if (cash->str)
	{
		free(cash->str);
		cash->str = NULL;
	}
	cash->len = new_len;
	return (1);
}

int	cash_read(t_cash **cash, int fd, int size)
{
	char	*read_buffer;
	ssize_t	read_sz;
	int		i;

	read_sz = -1;
	while (!cash_has_next_line(*cash))
	{
		read_buffer = (char *)ft_calloc(size, sizeof(char));
		if (read_buffer == NULL)
			return (clear_data(cash, NULL, -1));
		read_sz = read(fd, read_buffer, size);
		if (read_sz < 0)
			return (clear_data(cash, &read_buffer, -1));
		if (read_sz == 0)
			return (clear_data(NULL, &read_buffer, 0));
		if (!(cash_realloc(*cash, (*cash)->len + (int)read_sz, 0)))
			return (clear_data(cash, &read_buffer, -1));
		ft_strncat((*cash)->str, read_buffer, read_sz);
		free(read_buffer);
	}
	i = !(read_sz == 0);
	return (i);
}

int	cash_set_next_line(t_cash *cash, char **str)
{
	int		len;

	if (cash->next == -1)
		len = cash->len;
	else
		len = cash->next;
	*str = (char *)ft_calloc(len + 1, sizeof(char));
	if (*str == NULL)
		return (-1);
	if (len > 0)
		ft_strncat(*str, cash->str, len);
	return (1);
}
