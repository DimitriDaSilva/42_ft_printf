/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/21 18:48:19 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_types.h"

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @12-13	Edge case: when precision > lenght of number, add a padding of 0
**			until total length is equal to precision
** @14-19	Print based on the flag
*/

int	print_hex(t_format *settings)
{
	long long	nb_to_convert;
	int			nb_printed_chars;
	char		*str_to_print;

	nb_to_convert = va_arg(g_arg_list, long long);
	if (settings->type == 'x')
		str_to_print = ft_convert_base(nb_to_convert, "0123456789abcdef");
	else
		str_to_print = ft_convert_base(nb_to_convert, "0123456789ABCDEF");
	add_padding(&str_to_print, settings->precision);
	if (settings->flags[0] == '-')
		nb_printed_chars = print_left(str_to_print, settings, ' ');
	else if (settings->flags[0] == '0' && settings->precision == -1)
		nb_printed_chars = print_right(str_to_print, settings, '0');
	else
		nb_printed_chars = print_right(str_to_print, settings, ' ');
	free(str_to_print);
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
	if (settings->flags[0] == '-')
		nb_printed_chars = print_left("%", settings, ' ');
	else if (settings->flags[0] == '0')
		nb_printed_chars = print_right("%", settings, '0');
	else
		nb_printed_chars = print_right("%", settings, ' ');
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

	
	float_precision = settings->precision == -1 ? 6 : settings->precision;
	// printf("\nPrecision: %d\n", float_precision);
	nb_to_print = ft_ftoa(va_arg(g_arg_list, double), float_precision);
	// printf("\n%s\n", nb_to_print);
	add_padding(&nb_to_print, settings->precision);
	if (settings->flags[0] == '-')
		nb_printed_chars = print_left(nb_to_print, settings, ' ');
	else if (settings->flags[0] == '0' && settings->precision == -1)
		nb_printed_chars = print_right(nb_to_print, settings, '0');
	else
		nb_printed_chars = print_right(nb_to_print, settings, ' ');
	free(nb_to_print);
	return (nb_printed_chars);
}

/*
** If flag == '-' and width >= 0, the printed value is left aligned
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
**			- [char] when left aligned, no padding is inserted on the right
**                   of the printed value so here the padding is
**                   always a space. So it could be a constant but to
**                   keep the design pattern consistent, it's like that
** @return:	[int] number of printed characters
** Line-by-line comments:
** @6-7		Edge case: for an arg NULL char, the putstr doesn't print anything
**			Function requirements ask for a ^@ to be printed
** @8-10	Edge case: for duixX, if precision == 0 && nb = 0, nothing to print
**			We are printing all cases that do not verify this edge case
** @11		Width needs to take into account already printed characters
** @12-13	Printing width times a space
*/

int	print_left(char *str, t_format *settings, char padding)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (settings->type == 'p')
		nb_printed_chars += ft_putstr("0x");
	if (settings->type == 'c' && *str == 0)
		nb_printed_chars += ft_putchar(0);
	else if (!ft_strchr("duixX", settings->type) ||
			!(*str == '0' && settings->precision == 0))
		nb_printed_chars += ft_putstr(str);
	settings->width -= nb_printed_chars;
	while (settings->width-- > 0)
		nb_printed_chars += ft_putchar(padding);
	return (nb_printed_chars);
}

/*
** If there is no flag used or flag == '0' and width >= 0, the printed value
** is right aligned. Padded with '0' if '0' flag, otherwise with spaces
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
**			- [char] either '0' or ' ' depending on the flag and the type
**					as char and string can't be printed with the '0' flag
** @return:	[int] number of printed characters
** Line-by-line comments:
** @4-5		Edge case: when the number is negative, the minus sign goes before
**			the regular padding and before the padding from the precision
** @6-7		Edge case: when the char is 0 it still needs to print ^@ but
**			it isn't being accounted for on line 14
** @8-10	Edge case: for duixX, if precision == 0 && nb = 0, nothing to print
**			But the '0' is still being accounted for in the total in line 14
** @13		Width needs to take into account already printed characters
** @14		We need to make sure we are making space for the str to print
** @15-16	Printing width times a space or a '0'
** @19-20	Edge case: for an arg NULL char, the putstr doesn't print anything
**			Function requirements ask for a ^@ to be printed
** @21-23	Edge case: for duixX, if precision == 0 && nb = 0, nothing to print
**			We are printing all cases that do not verify this edge case
*/

int	print_right(char *str, t_format *settings, char padding)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (*str == '-' && padding == '0')
		nb_printed_chars += ft_putchar(*str++);
	if (settings->type == 'c' && *str == 0)
		settings->width--;
	else if (ft_strchr("duixX", settings->type) && *str == '0'
			&& settings->precision == 0)
		settings->width++;
	else if (settings->type == 'p')
		settings->width -= ft_strlen("0x");
	settings->width -= nb_printed_chars;
	settings->width -= ft_strlen(str);
	while (settings->width-- > 0)
		nb_printed_chars += ft_putchar(padding);
	if (settings->type == 'p')
		nb_printed_chars += ft_putstr("0x");
	if (settings->type == 'c' && *str == 0)
		nb_printed_chars += ft_putchar(0);
	else if (!ft_strchr("duixX", settings->type) ||
			!(*str == '0' && settings->precision == 0))
		nb_printed_chars += ft_putstr(str);
	return (nb_printed_chars);
}
