/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:29:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/22 21:20:01 by dda-silv         ###   ########.fr       */
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

char			*ft_ftoa(double nb, int precision)
{
	int		length;
	char	*str_nb;
	char	*tmp;

	length = precision > 0 ? get_size_dl(nb) + 1 + precision : get_size_dl(nb);
	if (!(str_nb = calloc(length + 1, sizeof(char))))
		return (0);
	tmp = ft_itoa(nb);
	if (-1 < nb && 1 / nb < 0 && (*str_nb = '-') != 0)
		ft_strlcpy(str_nb + 1, tmp, length - precision + 1);
	else
		ft_strlcpy(str_nb, tmp, length - precision + 1);
	free(tmp);
	if (precision > 0)
		str_nb[length - 1 - precision] = '.';
	while (precision-- > 0)
		str_nb[length - 1 - precision] = ft_abs(nb *= 10) % 10 + '0';
	str_nb = ft_round(nb, length, str_nb);
	return (str_nb);
}

/*
** Based on the remainder of nb, it will round the values
** @param:	- [double] value to be converted into string
**			- [int] total length of the number (sign incl.)
**			- [char *] string formatted float
** @return:	[char *] either the same or a new string (in case the rounding
**                   leads to an additional digit)
** Line-by-line comments:
** @4		In this function, we traverse the string/number from right to left
**			to be able to increment when necessary. -2 for '.' and for NULL
** @5		We need the nb and a remainder to access the value positioned in
**			index [length + 1]
** @6-11	Case: if the last displayed number is not a 9, we apply the
**			bankers rounding rule (aka round to even). As the number here
**			incremented is not a 9nine and won't cause consecutive rounding,
**			we return from the function
** @12-14	Case: the last number is a 9 and is incremented to '0'. We use
**			while loop because it can generate a cascade of rounding
** @14-16	Case: we just incremented a 9 to a 0 so we need to round up one
**			more number. We need to make sure we are not changing the '.' and
**			that we actually moved in the string/number
** @17-18	If we reached the . it means that the decimal part gets rounded up
*/

static char		*ft_round(double nb, int length, char *str_nb)
{
	double	remainder;
	int		index_last_number;

	index_last_number = length - 1;
	remainder = ft_remainder(nb * 10, 10);
	if (str_nb[index_last_number] != '9' && 5 == remainder)
	{
		if (!ft_is_even(str_nb[index_last_number]))
			str_nb[index_last_number] += 1;
		return (str_nb);
	}
	else if (str_nb[index_last_number] != '9' && 5 <= remainder)
	{
		str_nb[index_last_number] += 1;
		return (str_nb);
	}
	else if (str_nb[index_last_number] == '9' && 5 <= remainder &&
			!ft_strchr(str_nb, '.'))
	{
		str_nb = increment(str_nb, length);
		return (str_nb);
	}
	while (str_nb[index_last_number] == '9' && 5 <= remainder)
		str_nb[index_last_number--] = '0';
	if (ft_isdigit(str_nb[index_last_number]) &&
		index_last_number != length - 1)
		str_nb[index_last_number] += 1;
	else if (str_nb[index_last_number] == '.')
		str_nb = increment(str_nb, length);
	return (str_nb);
}

static double	ft_remainder(double numer, double denom)
{
	if (numer < 0)
		numer *= -1;
	return (numer - (denom * (long long)(numer / denom)));
}

/*
** If function called, after rounding up, the digits before the breakpoint
** need to also be rounded up. Possibly with an extra digit
** @param:	- [char *] string formatted float
**			- [int] total length of the number (sign incl.)
** @return:	[char *] new str with either the same number of chars or with
**                   an extra char (i.e. 99 -> 100)
** Line-by-line comments:
** @3		i = old string index
** @4		j = new string index
** @8		Finding the index of the decimal point by making the difference of
** 			addresses or last index digit if no decimal point
** @8		Adapting the index for the new string
** @9-10	If same length as before, we can simply copy everything and just
** 			change the relevant numbers
** @11-16	If not the same, we want to copy the '-' sign (if needed) and all
**			characters after the decimal point (if precision > 0)
** @17		Here we tackle the numbers before the decimal point
*/

static char		*increment(char *str_nb, int length)
{
	char	*new_str_nb;
	int		new_length;
	int		i;
	int		j;

	new_length = get_new_length(str_nb, length);
	if (!(new_str_nb = calloc(new_length + 1, sizeof(char))))
		return (0);
	i = ft_strchr(str_nb, '.') ? ft_strchr(str_nb, '.') - str_nb : length;
	j = new_length == length ? i : i + 1;
	if (new_length == length)
		ft_strlcpy(new_str_nb, str_nb, length + 1);
	else
	{
		if (*str_nb == '-')
			*new_str_nb = '-';
		if (ft_strchr(str_nb, '.'))
			ft_strlcpy(new_str_nb + j, str_nb + i, length - i + 1);
	}
	while (j-- >= 0 && (new_str_nb[j + 1] == '.' ||
			new_str_nb[j + 1] == '0' || new_str_nb[j + 1] == 0))
	{
		if (str_nb[--i] == 0 || str_nb[i] == '-')
			new_str_nb[j] = '1';
		else
			new_str_nb[j] = str_nb[i] == '9' ? '0' : str_nb[i] + 1;
	}
	free(str_nb);
	return (new_str_nb);
}

/*
** Check if the rounding requires a new digit (i.e. 99 -> 100)
** @param:	- [char *] string formatted float
**			- [int] total length of the number (sign incl.)
** @return:	[int] length + 1 if necessary
** Line-by-line comments:
** @5-6		If after traversing all digits == 9, we get to a '.', it must mean
**			that all numbers before the decimal point are ripe for a round up
*/

static int		get_new_length(char *str_nb, int length)
{
	if (*str_nb == '-')
		str_nb++;
	while (*str_nb == '9')
		str_nb++;
	if (*str_nb == '.' || *str_nb == 0)
		return (length + 1);
	else
		return (length);
}
