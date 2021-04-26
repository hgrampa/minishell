/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 11:09:38 by hgrampa           #+#    #+#             */
/*   Updated: 2021/01/23 11:14:40 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_gnl_service.h"

int	clear_data(t_cash **cash, char **str1, int result)
{
	if (cash != NULL && *cash != NULL)
	{
		if ((*cash)->str != NULL)
		{
			free((*cash)->str);
			(*cash)->str = NULL;
		}
		free(*cash);
		*cash = NULL;
	}
	if (str1 && *str1)
	{
		free(*str1);
		str1 = NULL;
	}
	return (result);
}

int	ft_gnl(int fd, char **line, int size)
{
	int				result;
	static t_cash	*cash;

	if (fd < 0 || !line || size <= 0)
		return (-1);
	if (cash == NULL)
	{
		cash = (t_cash *)ft_calloc(1, sizeof(t_cash));
		if (cash == NULL)
			return (-1);
	}
	result = cash_read(&cash, fd, size);
	if (result == -1)
		return (-1);
	if (!cash_set_next_line(cash, line))
		return (clear_data(&cash, NULL, -1));
	if (result == 0)
		return (clear_data(&cash, NULL, 0));
	else
	{
		if (!cash_realloc(cash, cash->len - cash->next - 1, cash->next + 1))
			return (clear_data(&cash, line, -1));
	}
	return (result);
}
