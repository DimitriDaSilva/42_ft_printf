/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:40:14 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/20 22:14:28 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_convert_base.h"

char		*ft_convert_base(long long nbr, char *base_to)
{
	int		nbr_converted_len;
	char	*nbr_converted;

	nbr_converted_len = length_nbr(nbr, base_to);
	nbr_converted = malloc(sizeof(char) * (nbr_converted_len + 2));
	*nbr_converted = '\0';
	if (nbr_converted == 0)
		return (0);
	ft_putnbr_base(nbr, base_to, nbr_converted);
	return (nbr_converted);
}

static int	length_nbr(long long nbr, char *base)
{
	int			base_size;
	int			count;
	long long	max;
	long long	tmp;

	base_size = 0;
	while (base[base_size] != '\0')
		base_size++;
	count = 0;
	max = 1;
	tmp = (nbr > 0) ? nbr : nbr * (-1);
	while (max <= tmp)
	{
		max = max * base_size;
		count++;
	}
	return (count);
}

static void	ft_putnbr_base(long long nbr, char *base, char *nbr_converted)
{
	int		base_size;

	if (nbr == 0)
	{
		*nbr_converted = base[0];
		*(nbr_converted + 1) = '\0';
		return ;
	}
	base_size = 0;
	while (base[base_size] != '\0')
		base_size++;
	convert(nbr, base, base_size, nbr_converted);
	return ;
}

static void	convert(long long nbr,
					char *base,
					int base_size,
					char *nbr_converted)
{
	if (nbr < 0)
	{
		ft_strncat(nbr_converted, "-", 1);
		nbr *= -1;
	}
	if (nbr > base_size - 1)
	{
		convert(nbr / base_size, base, base_size, nbr_converted);
		convert(nbr % base_size, base, base_size, nbr_converted);
	}
	else
		ft_strncat(nbr_converted, &base[nbr], 1);
}
