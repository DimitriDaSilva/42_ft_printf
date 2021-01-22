/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:29:52 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/22 13:36:04 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_print.h"

int			print_left_right(char *str, t_format *settings)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (ft_strchr(settings->flags, '-'))
		nb_printed_chars = print_left(str, settings);
	else
		nb_printed_chars = print_right(str, settings);
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

static int	print_left(char *str, t_format *settings)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (settings->type == 'c' && *str == 0)
		nb_printed_chars += ft_putchar(0);
	else if (!ft_strchr("duixX", settings->type) ||
			!(*str == '0' && settings->precision == 0))
		nb_printed_chars += ft_putstr(str);
	settings->width -= nb_printed_chars;
	while (settings->width-- > 0)
		nb_printed_chars += ft_putchar(' ');
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

static int	print_right(char *str, t_format *settings)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (settings->type == 'c' && *str == 0)
		settings->width--;
	else if (ft_strchr("duixX", settings->type) && *str == '0' &&
			settings->precision == 0)
		settings->width++;
	settings->width -= nb_printed_chars;
	settings->width -= ft_strlen(str);
	while (settings->width-- > 0)
		nb_printed_chars += ft_putchar(' ');
	if (settings->type == 'c' && *str == 0)
		nb_printed_chars += ft_putchar(0);
	else if (!ft_strchr("duixX", settings->type) ||
			!(*str == '0' && settings->precision == 0))
		nb_printed_chars += ft_putstr(str);
	return (nb_printed_chars);
}
