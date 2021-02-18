/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:40:14 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/18 10:45:05 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_convert_base.h"

char		*ft_convert_base(unsigned long long nbr, char *base_to)
{
	int		nbr_converted_len;
	char	*nbr_converted;
	int		base_size;

	base_size = ft_strlen(base_to);
	nbr_converted_len = length_nbr(nbr, base_size);
	if (!(nbr_converted = ft_calloc(nbr_converted_len + 2, sizeof(char))))
		return (0);
	ft_putnbr_base(nbr, base_to, base_size, nbr_converted);
	return (nbr_converted);
}

static int	length_nbr(unsigned long long nbr, int base_size)
{
	unsigned long long	count;
	unsigned long long	max;

	count = 0;
	max = 1;
	while (max <= nbr)
	{
		max *= base_size;
		count++;
		if (max == 1152921504606846976)
			break ;
	}
	return (count);
}

static void	ft_putnbr_base(unsigned long long nbr,
					char *base,
					int base_size,
					char *nbr_converted)
{
	if (nbr >= (unsigned long long)base_size)
	{
		ft_putnbr_base(nbr / base_size, base, base_size, nbr_converted);
		ft_putnbr_base(nbr % base_size, base, base_size, nbr_converted);
	}
	else
		ft_strncat(nbr_converted, &base[nbr], 1);
}
