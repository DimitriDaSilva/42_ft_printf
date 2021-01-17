/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 08:36:33 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/17 20:52:29 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	has_duplicate_chars(char *str)
{
	while (*str && *(str + 1) != '\0')
	{
		if (ft_strchr(str + 1, *str) != 0)
			return (1);
		str++;
	}
	return (0);
}

static int	is_base_valid(char *base)
{
	if (base == 0)
		return (0);
	else if (*base == '\0')
		return (0);
	else if (*(base + 1) == '\0')
		return (0);
	else if (has_duplicate_chars(base))
		return (0);
	else if (ft_strchr(base, '-') != 0 || ft_strchr(base, '+') != 0)
		return (0);
	else
		return (1);
}

static void	convert(long long nbr, char *base, int base_size)
{
	int remainder;

	remainder = 0;
	if (nbr == 0)
		return ;
	remainder = nbr % base_size;
	if (base_size * (-1) <= nbr && nbr <= -1 && remainder != 0)
		write(1, "-", 1);
	if (nbr < 0 && remainder != 0)
		nbr++;
	convert(nbr / base_size, base, base_size);
	if (remainder < 0)
		remainder *= -1;
	write(1, &base[remainder], 1);
	return ;
}

void		ft_putnbr_base(long long nbr, char *base)
{
	int	base_size;

	if (!is_base_valid(base))
		return ;
	if (nbr == 0)
	{
		write(1, &base[0], 1);
		return ;
	}
	base_size = 0;
	while (base[base_size] != '\0')
		base_size++;
	convert(nbr, base, base_size);
}
