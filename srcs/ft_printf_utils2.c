/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:34:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/23 21:58:16 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_exponent(double *nb, char **exponent)
{
	int 	count;
	double	cpy;

	count = 0;
	cpy = *nb;
	while ((-1 < *nb && 1 / *nb < 0) || (0 < *nb && *nb < 1))
	{
		*nb *= 10;
		if (cpy == *nb)
			break ;
		count--;
	}
	while (*nb < -10 || 10 < *nb)
	{
		*nb /= 10;
		count++;
	}
	*exponent = ft_itoa(count);
	add_sign(exponent, "+");
	add_padding(exponent, 2);
}

void	add_exponent(char **nb, char **exponent)
{
	int		i;
	char	*tmp;

	i = ft_strlen(*nb);
	if (!(tmp = malloc((i + 4 + 1) * sizeof(char))))
		return ;
	ft_strcpy(tmp, *nb);
	tmp[i] = 'e'; 
	tmp[i + 1] = 0;
	ft_strncat(tmp + i + 1, *exponent, 3);
	tmp[i + 5] = '\0';
	free(*exponent);
	free(*nb);
	*nb = tmp;
}
