/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 12:31:59 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/18 12:36:33 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long long n)
{
	char	*str;
	size_t	size_nbr;

	size_nbr = get_size_lg(n);
	if (!(str = ft_calloc(size_nbr + 1, sizeof(char))))
		return (0);
	str += size_nbr - 1;
	while (size_nbr--)
	{
		if (n == LONG_MIN || n == LONG_MAX)
			*str-- = '8';
		else
			*str-- = ft_abs(n) % 10 + ASCII_OFFSET_NUM;
		if (-10 < n && n < 0)
		{
			*str-- = '-';
			break ;
		}
		n /= 10;
	}
	return (++str);
}
