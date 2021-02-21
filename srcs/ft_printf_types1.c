/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/21 20:05:11 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_types.h"

/*
** Call different print function depending on the type and passing doing the
** settings gathered by get_settings()
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
*/

void	print_types(t_format *settings)
{
	if ('c' == settings->type)
		print_char(settings);
	else if ('s' == settings->type)
		print_str(settings);
	else if ('p' == settings->type)
		print_ptr(settings);
	else if (ft_strchr("di", settings->type))
		print_int_signed(settings);
	else if ('u' == settings->type)
		print_int_unsigned(settings);
	else if (ft_strchr("xX", settings->type))
		print_hex(settings);
	else if ('%' == settings->type)
		print_pct(settings);
	else if ('n' == settings->type)
		print_n(settings);
	else if ('f' == settings->type)
		print_flt(settings);
	else if ('e' == settings->type)
		print_exp(settings);
	else if ('g' == settings->type)
		print_g(settings);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** Line-by-line comments:
** @4-11	Case: %lc (wide character that can be from 1 to 3 bytes).
**			We are converting the wide char into a string based on UTF
**			encoding
** @7		We check how many single-byte char will be needed to convert from
**			wide char to UTF encoding (it can be from 1 to 4 bytes based on the
**			value of the binary representing the wide char)
** @8		Convert wide character to single-byte string
** @12-17	Case: %c
*/

void	print_char(t_format *settings)
{
	char	*str_to_print;
	wchar_t	wc;

	if (!ft_strncmp(settings->size, "l", 2))
	{
		wc = va_arg(g_arg_list, wchar_t);
		str_to_print = ft_calloc(ft_wclen(wc) + 1, sizeof(char));
		if (!str_to_print)
			return ;
		ft_wctostr(str_to_print, wc, ft_wclen(wc));
	}
	else
	{
		if (!(str_to_print = ft_calloc(2, sizeof(char))))
			return ;
		*str_to_print = va_arg(g_arg_list, int);
	}
	print_left_right(settings, str_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** Line-by-line comments:
** @4-11	Case: %ls (wide character string)
**			We are converting the wide char string into a string based on UTF
**			encoding
** @6		We check how many single-byte char will be needed to convert from
**			wide char string to char string based on UTF encoding
**			Each wide char of the string can require up to 4 byte (i.e. 4 chars)
** @12-13	Case: %s
** @14-15	Edge case: NULL pointer passed as arg
** @16-17	Edge case: empty string (i.e. "") passed as arg. We need to check
**			we aren't in a %ls case, in which case we already allocated 1 byte
**			with a NULL terminator
** @18-19	Standard %s case but we need to make sure we are in %ls case
**			because the str_to_print has already been allocated
** 			Also in std case, we need to work with a duplicate because arg is
**			const
** @20-22	Edge case: A precision has been set and it's lower than the size
**			of the string to print ==> cut str by adding a NULL at precision
*/

void	print_str(t_format *settings)
{
	char	*str_to_print;
	wchar_t	*wstr;

	if (!ft_strncmp(settings->size, "l", 2))
	{
		wstr = va_arg(g_arg_list, wchar_t *);
		str_to_print = ft_calloc(ft_wstrlen(wstr) + 1, sizeof(char));
		if (!str_to_print)
			return ;
		ft_wstrtostr(str_to_print, wstr, ft_wstrlen(wstr));
	}
	else
		str_to_print = va_arg(g_arg_list, char *);
	if (!str_to_print)
		str_to_print = ft_strdup("(null)");
	else if (!*str_to_print && ft_strncmp(settings->size, "l", 2))
		str_to_print = ft_strdup("");
	else if (ft_strncmp(settings->size, "l", 2))
		str_to_print = ft_strdup(str_to_print);
	if (settings->precision != -1 &&
		settings->precision < (int)ft_strlen(str_to_print))
		str_to_print[settings->precision] = 0;
	print_left_right(settings, str_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** Line-by-line comments:
** @5-6		Edge case: for pointers, when value = 0, print 0x0. Needs a
**			special case because add_hex_prefix() isn't supposed to put
**			0x prefix if the number is all zeros
*/

void	print_ptr(t_format *settings)
{
	unsigned long long	nb_to_convert;
	char				*nb_to_print;

	nb_to_convert = va_arg(g_arg_list, unsigned long long int);
	if (nb_to_convert == 0)
		nb_to_print = ft_strdup("0x0");
	else
		nb_to_print = ft_convert_base(nb_to_convert, "0123456789abcdef");
	if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	if (nb_to_convert != 0)
		add_hex_prefix(&nb_to_print, settings->type, settings->flags);
	print_left_right(settings, nb_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** Line-by-line comments:
** @9-13	Adding the padding of '0' associated with the '0' flags. The 0s
**			go before the signs
** @14		Adding the padding of '0' associated with the fact that precision
**			would be higher than length of number (if so left-padded with 0)
*/

void	print_hex(t_format *settings)
{
	unsigned long long	nb_to_convert;
	char				*nb_to_print;

	if (!ft_strncmp(settings->size, "ll", 3))
		nb_to_convert = va_arg(g_arg_list, unsigned long long);
	else if (!ft_strncmp(settings->size, "l", 2))
		nb_to_convert = va_arg(g_arg_list, unsigned long);
	else if (!ft_strncmp(settings->size, "hh", 3))
		nb_to_convert = (unsigned char)va_arg(g_arg_list, unsigned int);
	else if (!ft_strncmp(settings->size, "h", 2))
		nb_to_convert = (short unsigned)va_arg(g_arg_list, unsigned int);
	else
		nb_to_convert = va_arg(g_arg_list, unsigned int);
	if (settings->type == 'x')
		nb_to_print = ft_convert_base(nb_to_convert, "0123456789abcdef");
	else
		nb_to_print = ft_convert_base(nb_to_convert, "0123456789ABCDEF");
	if (ft_strchr(settings->flags, '#') && ft_strchr(settings->flags, '0') &&
		!is_all_zeros(nb_to_print))
		add_padding(&nb_to_print, settings->width - 2);
	else if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	add_padding(&nb_to_print, settings->precision);
	add_hex_prefix(&nb_to_print, settings->type, settings->flags);
	print_left_right(settings, nb_to_print);
}
