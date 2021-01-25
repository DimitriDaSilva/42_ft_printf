/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 20:22:59 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/25 08:26:35 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	get_count_int(double nb)
{
	size_t	count;

	nb = ft_abs_dl(nb);
	if (nb < 1)
		return (1);
	count = 0;
	while (nb > 1)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

void	remove_trailing_zero(char *nb)
{
	if (*nb == '-')
		nb++;
	if (*nb == '0')
		nb++;
	while(*nb && !is_all_zeros(nb))
		nb++;
	if (*nb == 0)
		return ;
	else if (*(nb - 1) == '.')
		*(nb - 1) = 0;
	else
		*nb = 0;
}

void	remove_middle_zero(char *nb)
{
	int 	i;
	size_t	length;

	length = ft_strlen(nb);
	i = length - 1;
	while (nb[i + 1] != 'e')
		i--;
	while (nb[i] == '0')
		i--;
	if (i == 0)
		return ;
	else if (nb[i] == '.')
		ft_strlcpy(nb + i, nb + length - 4, 5);
	else
		ft_strlcpy(nb + i + 1, nb + length - 4, 5);
}