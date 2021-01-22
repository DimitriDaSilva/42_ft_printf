/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/22 13:31:05 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_types.h"

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @8		Add sign ' ' or '+' basde on the flag used
**			'-' sign is handled by ft_itoa()
** @9		Edge case: when precision > lenght of number, add a padding of 0
**			until total length is equal to precision
** @10-11	Edge case: if precision == 0, nb = 0 and flag = '+', only the '+'
**			is printed
** @12-17	Print based on the flag
*/

int	print_int(t_format *settings)
{
	int		nb_printed_chars;
	char	*nb_to_print;

	nb_printed_chars = 0;
	if (settings->type == 'd' || settings->type == 'i')
		nb_to_print = ft_itoa(va_arg(g_arg_list, int));
	else if (settings->type == 'u')
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
** @8-9		Edge case: if precision == 0 && nb = 0, nothing at all to print
** 			A space has been put as the first char of the nb_to_print to signal
**			the subsequent function that this is a special case
** @10-12	Edge case: when precision > lenght of number, add a padding of 0
**			until total length is equal to precision
** @12-17	Print based on the flag
*/

int	print_flt(t_format *settings)
{
	int		nb_printed_chars;
	char	*nb_to_print;
	int		float_precision;

	nb_printed_chars = 0;
	if (ft_strchr(settings->flags, '#'))
		float_precision = 1;
	else
		float_precision = settings->precision == -1 ? 6 : settings->precision;
	nb_to_print = ft_ftoa(va_arg(g_arg_list, double), float_precision);
	add_sign(&nb_to_print, settings->flags);
	if (ft_strchr(settings->flags, '0'))
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
