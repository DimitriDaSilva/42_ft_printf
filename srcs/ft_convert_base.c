/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:40:14 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/17 22:19:09 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_convert_base.h"

char		*ft_convert_base(unsigned long long nbr, char *base_to)
{
	int		nbr_converted_len;
	char	*nbr_converted;

	nbr_converted_len = length_nbr(nbr, base_to);
	if (!(nbr_converted = ft_calloc(nbr_converted_len + 2, sizeof(char))))
		return (0);
	ft_putnbr_base(nbr, base_to, nbr_converted);
	return (nbr_converted);
}

static int	length_nbr(unsigned long long nbr, char *base)
{
	int					base_size;
	int					count;
	unsigned long long	max;
	unsigned long long	tmp;

	base_size = ft_strlen(base);
	count = 0;
	max = 1;
	tmp = ft_abs(nbr);
	while (max <= tmp)
	{
		max = max * base_size;
		count++;
		if (max == 1152921504606846976)
			break ;
	}
	return (count);
}

static void	ft_putnbr_base(unsigned long long nbr,
							char *base,
							char *nbr_converted)
{
	int		base_size;

	if (nbr == 0)
	{
		*nbr_converted = base[0];
		*(nbr_converted + 1) = '\0';
		return ;
	}
	base_size = ft_strlen(base);
	convert(nbr, base, base_size, nbr_converted);
	return ;
}

static void	convert(unsigned long long nbr,
					char *base,
					int base_size,
					char *nbr_converted)
{
	if (nbr > (unsigned long long)(base_size - 1))
	{
		convert(nbr / base_size, base, base_size, nbr_converted);
		convert(nbr % base_size, base, base_size, nbr_converted);
	}
	else
		ft_strncat(nbr_converted, &base[nbr], 1);
}
