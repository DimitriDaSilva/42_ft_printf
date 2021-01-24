/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 20:34:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/24 20:22:40 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_exp_str(double *nb, char **exponent)
{
	int		count;
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

void	adjust_rounding(char *nb)
{
	int		length;
	int		i;
	char	sign_exp;

	if ((nb[0] == '-' && (nb[2] == '.' || nb[2] == 'e')) ||
		(nb[0] != '-' && (nb[1] == '.' || nb[1] == 'e')))
		return ;
	length = ft_strlen(nb);
	sign_exp = nb[length - 3] == '+' ? '+' : '-';
	i = 0;
	while (nb[i] != '0')
		i++;
	nb[i - 1] = '1';
	if (nb[i + 1] == '.')
		nb[i++] = '.';
	while (nb[i + 1] != 'e')
		nb[i++] = '0';
	if (!ft_strncmp(nb + length - 4, "e-01", 5))
		ft_strncpy(nb + length - 5, "e+00", 5);
	else
	{
		increment(nb + length - 2, sign_exp);
		ft_strlcpy(nb + i, nb + length - 4, 5);
	}
}

void	increment(char *nb, char sign)
{
	int		i;

	i = ft_strlen(nb);
	while (i-- >= 0 && (nb[i + 1] == '0' || nb[i + 1] == '\0'))
	{
		if (sign == '+')
			nb[i] = nb[i] == '9' ? '0' : nb[i] + 1;
		else
			nb[i] = nb[i] == '0' ? '9' : nb[i] - 1;
	}
}

int		get_exp_nb(double nb)
{
	int		count;
	double	cpy;

	count = 0;
	cpy = nb;
	while ((-1 < nb && 1 / nb < 0) || (0 < nb && nb < 1))
	{
		nb *= 10;
		if (cpy == nb)
			break ;
		count--;
	}
	nb = ft_round(nb);
	while (nb <= -10 || 10 <= nb)
	{
		nb /= 10;
		count++;
	}
	return (count);
}
