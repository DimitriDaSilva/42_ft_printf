/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/21 18:17:52 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_types.h"

/*
** Call different print function depending on the type
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
*/

int	print(t_format *settings)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if ('c' == settings->type)
		nb_printed_chars = print_char(settings);
	else if ('s' == settings->type)
		nb_printed_chars = print_str(settings);
	else if ('p' == settings->type)
		nb_printed_chars = print_ptr(settings);
	else if (ft_strchr("diu", settings->type))
		nb_printed_chars = print_int(settings);
	else if (ft_strchr("pxX", settings->type))
		nb_printed_chars = print_hex(settings);
	else if ('%' == settings->type)
		nb_printed_chars = print_pct(settings);
	else if ('f' == settings->type)
		nb_printed_chars = print_flt(settings);
	return (nb_printed_chars);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @8-9		Malloc of size 2 because: (size of '-' or '0') + (size of '\0')
** @7-10	Print based on the flag
*/

int	print_char(t_format *settings)
{
	int		nb_printed_chars;
	char	*str;

	if (!(str = calloc(2, sizeof(char))))
		return (0);
	str[0] = va_arg(g_arg_list, int);
	if (settings->flags[0] == '-')
		nb_printed_chars = print_left(str, settings, ' ');
	else if (settings->flags[0] == 0)
		nb_printed_chars = print_right(str, settings, ' ');
	free(str);
	return (nb_printed_chars);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @4-6		Get argument from arg_list. If arg = NULL, print (null)
**			Edge case: Precision allow enough spacae to print (null)
** @7-8		Edge case: arg = NULL but precision doesn't allow enough space
** 			to print (null), so return emptyable string
** @9-10	Need to work with a duplicate because arg is const
** @11-12	Edge case: A precision has been set and it's lower than the size
**			of the string to print ==> cut str by adding a NULL at precision
** @13-16	Print based on the flag
*/

int	print_str(t_format *settings)
{
	int		nb_printed_chars;
	char	*str;

	if (!(str = va_arg(g_arg_list, char *)) &&
		(settings->precision >= 6 || settings->precision <= -1))
		str = ft_strdup("(null)");
	else if ((!str && settings->precision < 6) || !*str)
		str = ft_strdup("");
	else
		str = ft_strdup(str);
	if (settings->precision != -1 && settings->precision < (int)ft_strlen(str))
		str[settings->precision] = 0;
	if (settings->flags[0] == '-')
		nb_printed_chars = print_left(str, settings, ' ');
	else if (settings->flags[0] == 0)
		nb_printed_chars = print_right(str, settings, ' ');
	free(str);
	return (nb_printed_chars);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @11-14	Print based on the flag
*/

int	print_ptr(t_format *settings)
{
	long long	nb_to_convert;
	int			nb_printed_chars;
	char		*str_to_print;

	nb_printed_chars = 0;
	nb_to_convert = va_arg(g_arg_list, long long);
	if (nb_to_convert == 0)
		return (ft_putstr("(nil)"));
	else
		str_to_print = ft_convert_base(nb_to_convert, "0123456789abcdef");
	if (settings->flags[0] == '-')
		nb_printed_chars += print_left(str_to_print, settings, ' ');
	else if (settings->flags[0] == 0)
		nb_printed_chars += print_right(str_to_print, settings, ' ');
	free(str_to_print);
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

int	print_int(t_format *settings)
{
	int		nb_printed_chars;
	char	*nb_to_print;

	if (settings->type == 'd' || settings->type == 'i')
		nb_to_print = ft_itoa(va_arg(g_arg_list, int));
	else if (settings->type == 'u')
		nb_to_print = ft_itoa(va_arg(g_arg_list, unsigned int));
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
