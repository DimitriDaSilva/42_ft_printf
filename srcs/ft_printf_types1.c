/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/20 10:45:33 by dda-silv         ###   ########.fr       */
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
*/

void	print_char(t_format *settings)
{
	char	*str_to_print;
	wchar_t	*w_str;

	if (!ft_strncmp(settings->size, "l", 2))
	{
		if (!(str_to_print = ft_calloc(1, sizeof(wchar_t))))
			return ;
		if (!(w_str = ft_calloc(2, sizeof(wchar_t))))
			return ;
		*w_str = va_arg(g_arg_list, unsigned int);
		wcstombs(str_to_print, w_str, sizeof(str_to_print));
		free(w_str);
	}
	else
	{
		if (!(str_to_print = ft_calloc(2, sizeof(char))))
			return ;
		*str_to_print = va_arg(g_arg_list, int);
	}
		print_left_right(settings, str_to_print);
		free(str_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** Line-by-line comments:
** @3-4		Get argument from arg_list. If arg = NULL, print (null)
**			Edge case: Precision allow enough spacae to print (null)
** @6-7		Edge case: arg = NULL but precision doesn't allow enough space
** 			to print (null), so return emptyable string
** @8-9		Need to work with a duplicate because arg is const
** @10-12	Edge case: A precision has been set and it's lower than the size
**			of the string to print ==> cut str by adding a NULL at precision
*/

void	print_str(t_format *settings)
{
	char	*str_to_print;
	wchar_t	*w_str;

	if (!ft_strncmp(settings->size, "l", 2))
	{
		w_str = va_arg(g_arg_list, wchar_t *);
		if (!(str_to_print = ft_calloc(ft_wcslen(w_str), sizeof(wchar_t))))
			return ;
		wcstombs(str_to_print, w_str, ft_wcslen(w_str) * sizeof(wchar_t));
	}
	else
		str_to_print = va_arg(g_arg_list, char *);
	if (!str_to_print)
		str_to_print = ft_strdup("(null)");
	else if (!*str_to_print)
		str_to_print = ft_strdup("");
	else if (ft_strncmp(settings->size, "l", 2))
		str_to_print = ft_strdup(str_to_print);
	if (settings->precision != -1 &&
		settings->precision < (int)ft_strlen(str_to_print))
		str_to_print[settings->precision] = 0;
	print_left_right(settings, str_to_print);
	free(str_to_print);
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
	free(nb_to_print);
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
	else
		nb_to_convert = va_arg(g_arg_list, unsigned int);
	if (settings->type == 'x')
		nb_to_print = ft_convert_base((unsigned long long)nb_to_convert, "0123456789abcdef");
	else
		nb_to_print = ft_convert_base((unsigned long long)nb_to_convert, "0123456789ABCDEF");
	if (ft_strchr(settings->flags, '#') && ft_strchr(settings->flags, '0') &&
		!is_all_zeros(nb_to_print))
		add_padding(&nb_to_print, settings->width - 2);
	else if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	add_padding(&nb_to_print, settings->precision);
	add_hex_prefix(&nb_to_print, settings->type, settings->flags);
	print_left_right(settings, nb_to_print);
	free(nb_to_print);
}
