/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:55:24 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/16 18:49:08 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		convert_to_char(int nb)
{
	if (nb < 0)
	{
		nb *= -1;
	}
	return (nb + ASCII_OFFSET_NUM);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	n_to_print;
	char	hyphen;
	int		remainder;

	if (0 <= n && n < 10)
	{
		n_to_print = convert_to_char(n);
		write(fd, &n_to_print, 1);
		return ;
	}
	else if (-10 < n && n < 0)
	{
		hyphen = '-';
		write(fd, &hyphen, 1);
		n_to_print = convert_to_char(n);
		write(fd, &n_to_print, 1);
		return ;
	}
	remainder = n % 10;
	ft_putnbr_fd(n / 10, fd);
	n_to_print = convert_to_char(remainder);
	write(fd, &n_to_print, 1);
	return ;
}
