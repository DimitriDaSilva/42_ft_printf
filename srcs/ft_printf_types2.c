/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/23 12:57:52 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_types.h"

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @8		Add sign ' ' or '+' based on the flag used
**			'-' sign is handled by ft_itoa()
** @9		Edge case: when precision > lenght of number, add a padding of 0
**			until total length is equal to precision
** @12-15	Adding the padding of '0'. The 0s go before the signs
** @17-18	Edge case: if precision == 0, nb = 0 and flag = '+', only the '+'
**			is printed
*/

int	print_int(t_format *settings)
{
	int		nb_printed_chars;
	char	*nb_to_print;

	nb_printed_chars = 0;
	if (!ft_strncmp(settings->size, "ll", 3))
		nb_to_print = ft_itoa(va_arg(g_arg_list, long long int));
	else if (!ft_strncmp(settings->size, "l", 2))
		nb_to_print = ft_itoa(va_arg(g_arg_list, long int));
	else
		nb_to_print = ft_itoa(va_arg(g_arg_list, int));
	add_sign(&nb_to_print, settings->flags);
	if (ft_strchr(settings->flags, '0') && ft_strchr("+- ", *nb_to_print))
		add_padding(&nb_to_print, settings->width - 1);
	else if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	add_padding(&nb_to_print, settings->precision);
	if (!ft_strncmp(nb_to_print, "+0", 3) && settings->precision == 0)
		nb_to_print[1] = '\0';
	nb_printed_chars += print_left_right(nb_to_print, settings);
	free(nb_to_print);
	return (nb_printed_chars);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @8		Add sign ' ' or '+' based on the flag used
**			'-' sign is handled by ft_itoa()
** @9		Edge case: when precision > lenght of number, add a padding of 0
**			until total length is equal to precision
** @12-15	Adding the padding of '0'. The 0s go before the signs
** @17-18	Edge case: if precision == 0, nb = 0 and flag = '+', only the '+'
**			is printed
*/

int	print_uint(t_format *settings)
{
	int		nb_printed_chars;
	char	*nb_to_print;

	nb_printed_chars = 0;
	if (!ft_strncmp(settings->size, "ll", 3))
		nb_to_print = ft_itoa(va_arg(g_arg_list, unsigned long long int));
	else if (!ft_strncmp(settings->size, "l", 2))
		nb_to_print = ft_itoa(va_arg(g_arg_list, long unsigned int));
	else
		nb_to_print = ft_itoa(va_arg(g_arg_list, unsigned int));
	add_sign(&nb_to_print, settings->flags);
	if (ft_strchr(settings->flags, '0') && ft_strchr("+- ", *nb_to_print))
		add_padding(&nb_to_print, settings->width - 1);
	else if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	add_padding(&nb_to_print, settings->precision);
	if (!ft_strncmp(nb_to_print, "+0", 3) && settings->precision == 0)
		nb_to_print[1] = '\0';
	nb_printed_chars += print_left_right(nb_to_print, settings);
	free(nb_to_print);
	return (nb_printed_chars);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @6		-1 means no precision as been specified. 6 is the default
** @8		If the flags # is used, if forces a decimal point (even if
**			precision == 0)
** @10-13	Adding the padding of '0'. The 0s go before the signs
*/

int	print_flt(t_format *settings)
{
	int		nb_printed_chars;
	char	*nb_to_print;
	int		float_precision;

	nb_printed_chars = 0;
	float_precision = settings->precision <= -1 ? 6 : settings->precision;
	nb_to_print = ft_ftoa(va_arg(g_arg_list, double), float_precision);
	add_point(&nb_to_print, settings);
	add_sign(&nb_to_print, settings->flags);
	if (ft_strchr(settings->flags, '0') && ft_strchr("+- ", *nb_to_print))
		add_padding(&nb_to_print, settings->width - 1);
	else if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	add_padding(&nb_to_print, settings->precision);
	nb_printed_chars += print_left_right(nb_to_print, settings);
	free(nb_to_print);
	return (nb_printed_chars);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
*/

int	print_pct(t_format *settings)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	settings->width = 0;
	nb_printed_chars += print_left_right("%", settings);
	return (nb_printed_chars);
}
