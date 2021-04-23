/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgrampa <hgrampa@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 10:44:12 by hgrampa           #+#    #+#             */
/*   Updated: 2020/11/27 15:15:55 by hgrampa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	write_num_rank(long num, int fd)
{
	char	number;

	if (num > 0)
	{
		write_num_rank(num / 10, fd);
		number = _FT_ASCII_NUM_OFFSET + num % 10;
		write(fd, &number, sizeof(char));
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long	number;

	number = (long)n;
	if (n < 0)
	{
		write(fd, "-", sizeof(char));
		number *= -1;
	}
	if (n == 0)
		write(fd, "0", sizeof(char));
	else
		write_num_rank(number, fd);
}
