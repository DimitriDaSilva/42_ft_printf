/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:29:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/21 20:02:17 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ftoa.h"

/*
** Converts a float to a string
** @param:	- [float] nb to convert
**			- [int] nb of digits after the decimal point
** @return:	[char *] string formatted float number
** Line-by-line comments:
** @5		Size = length of decimal number + decimal point + nb of digits
**			to put after the comma
** @8-10	Extracting the decimal part of the number and copying it to
**			the new_string 
*/

char	*ft_ftoa(double nb, int precision)
{
	int		length;
	char	*str_nb;
	char	*tmp;

	// printf("%.40lf\n", nb);
	
	// if (1 / nb > 0)
	// 	printf("%s\n", "positive");
	// else if (1 / nb < 0)
	// 	printf("%s\n", "negative");
	// else
	// 	printf("%s\n", "null");
	if (precision <= 0 && -0.5 < nb && 1 / nb < 0)
		return (ft_strdup("-0"));
	else if (precision <= 0)
		return (ft_itoa((float)nb));
	length = get_size_nbr(nb) + 1 + precision;
	// printf("\nLength: %d\n", length);
	if (!(str_nb = calloc(length + 1, sizeof(char))))
		return (0);
	tmp = ft_itoa(nb);
	// printf("\n\"%s\"\n", tmp);
	if (-1 < nb && 1 / nb < 0 && (*str_nb = '-') != 0)
		ft_strlcpy(str_nb + 1, tmp, length - precision);
	else
		ft_strlcpy(str_nb, tmp, length - precision);
	free(tmp);
	str_nb[length - 1 - precision] = '.';
	while (precision-- > 0)
		str_nb[length - 1 - precision] = ft_abs(nb *= 10) % 10 + ASCII_OFFSET_NUM;
	ft_round(nb, length, str_nb, precision);
	return (str_nb);
}

static void	ft_round(double nb, int length, char *str_nb, int precision)
{
	double remainder;
	int	index_last_number;

	index_last_number = length - 2 - precision;
	// printf("Before rounding up: \"%s\"\n", str_nb);
	// printf("Precision: %i\n", precision);
	remainder = ft_remainder(nb * 10, 10);
	// printf("Remainder: %lf\n", remainder);
	// remainder = ft_abs(nb * 10) % 10;
	// printf("Remainder: %lf\n", remainder);
	// printf("Last digit: %c\n", str_nb[index_last_number]);
	// if (str_nb[index_last_number] == '8' && 5 <= remainder)
	// {
	// 	str_nb[index_last_number] += 1;
	// 	return ;
	// }
	if (str_nb[index_last_number] != '9' && 5 <= remainder &&
		!ft_is_even(str_nb[index_last_number]))
	{
		str_nb[index_last_number] += 1;
		return ;
	}
	// printf("Mid rounding up: \"%s\"\n", str_nb);
	while (str_nb[index_last_number] == '9' && 5 <= remainder)
		str_nb[index_last_number--] = '0';
	if (ft_isdigit(str_nb[index_last_number]) && 5 <= remainder &&
		ft_is_even(str_nb[index_last_number]) &&
		index_last_number != length - 2 - precision)
		str_nb[index_last_number] += 1;
	else if (ft_isdigit(str_nb[index_last_number]) && 5 <= remainder &&
		!ft_is_even(str_nb[index_last_number]))
		str_nb[index_last_number] += 1;
	// while (precision-- > 0)
	// 	str_nb[length - 1 - precision] = ft_abs(nb *= 10) % 10 + ASCII_OFFSET_NUM;
	// else if (str_nb[index_last_number] == '.')
	// 	printf("%s\n", "hey");
	// printf("After rounding up: \"%s\"\n", str_nb);
}

static double	ft_remainder(double numer, double denom)
{
	// double	res;
	
	if (numer < 0)
		numer *= -1;
	return (numer - (denom *(long long)(numer / denom)));
}

static int		ft_is_even(int c)
{
	return (c % 2 == 0);
}


// int	main(int argc, char *argv[])
// {
// 	(void)argc;
// 	(void)argv;
// 	// double	nb = 999.999999;
// 	// double	nb = -999.999999;
// 	// double	nb = 23.375094499;
// 	// double	nb = -0.00032;
// 	// double	nb = 3.85;
// 	// double	nb = 3.850;
// 	double	nb = -3.085;
// 	// double	nb = -3.00065;
// 	// double	nb = 45.456954266465;
// 	// double	nb = -45.456954266465;
// 	// int		digits = 2;

// 	// printf("Mine: %s\n", ft_ftoa(nb, 6));
// 	// for (float i = 0.05; i < 3.1; i += 0.10)
// 	// {
// 	// 	printf("%%.2f: %.2f | ", i);
// 	// 	printf("%%.1f: %.1f\n", i);
// 	// 	printf("\n");

// 	// }
// 	// printf("Orig: %.1f\n", 3.05);
// 	// printf("Orig: %.6lf\n", 999.999999);
// 	// ft_ftoa(nb, 4);
// 	for (int i = 0; i < 14; i++)
// 	{
// 		printf("Precision: %d\n", i);
// 		printf("\n");
// 		printf("Mine: %s\n", ft_ftoa(nb, i));
// 		printf("Orig: %.*f\n", i, nb);
// 		printf("\n");
// 		printf("----------------------------\n");
// 		printf("\n");
// 	}
// 	return (0);

// }