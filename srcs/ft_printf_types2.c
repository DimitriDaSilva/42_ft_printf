/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/23 17:25:43 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_types.h"

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @9		Add sign ' ' or '+' based on the flag used
**			'-' sign is handled by ft_itoa()
** @10-13	Adding the padding of '0'. The 0s go before the signs
** @15-16	Edge case: if precision == 0, nb = 0 and flag = '+', only the '+'
**			is printed
*/

void	print_int(t_format *settings)
{
	char	*nb_to_print;

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
	print_left_right(nb_to_print, settings);
	free(nb_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @9		Add sign ' ' or '+' based on the flag used
**			'-' sign is handled by ft_itoa()
** @10-13	Adding the padding of '0'. The 0s go before the signs
** @15-16	Edge case: if precision == 0, nb = 0 and flag = '+', only the '+'
**			is printed
*/

void	print_uint(t_format *settings)
{
	char	*nb_to_print;

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
	print_left_right(nb_to_print, settings);
	free(nb_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @4		-1 means no precision as been specified. 6 is the default
** @6		If the flags # is used, if forces a decimal point (even if
**			precision == 0)
** @8-11	Adding the padding of '0'. The 0s go before the signs
*/

void	print_flt(t_format *settings)
{
	char	*nb_to_print;
	int		float_precision;

	float_precision = settings->precision <= -1 ? 6 : settings->precision;
	nb_to_print = ft_ftoa(va_arg(g_arg_list, double), float_precision);
	add_point(&nb_to_print, settings);
	add_sign(&nb_to_print, settings->flags);
	if (ft_strchr(settings->flags, '0') && ft_strchr("+- ", *nb_to_print))
		add_padding(&nb_to_print, settings->width - 1);
	else if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	add_padding(&nb_to_print, settings->precision);
	print_left_right(nb_to_print, settings);
	free(nb_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
*/

void	print_pct(t_format *settings)
{
	settings->width = 0;
	print_left_right("%", settings);
}

/*
** The n specifier receives a pointer to an int as an arg. It puts number of
** printed char in this variable
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
*/

void	print_n(t_format *settings)
{
	long long int	*nb;

	if (!ft_strncmp(settings->size, "ll", 3))
		nb = va_arg(g_arg_list, long long int *);
	else if (!ft_strncmp(settings->size, "l", 2))
		nb = (long long int *)va_arg(g_arg_list, long int *);
	else
		nb = (long long int *)va_arg(g_arg_list, int *);
	*nb = g_count_printed_ch;
}
