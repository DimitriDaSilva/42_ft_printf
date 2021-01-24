/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 19:53:42 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/24 11:47:33 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_types.h"

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
	print_left_right(settings, nb_to_print);
	free(nb_to_print);
}

void	print_exp(t_format *settings)
{
	char	*nb_to_print;
	int		float_precision;
	char	*exponent;
	double	nb;

	float_precision = settings->precision <= -1 ? 6 : settings->precision;
	nb = va_arg(g_arg_list, double);
	get_exponent(&nb, &exponent);
	nb_to_print = ft_ftoa(nb, float_precision);
	add_point(&nb_to_print, settings);
	add_exponent(&nb_to_print, &exponent);
	adjust_rounding(nb_to_print);
	add_sign(&nb_to_print, settings->flags);
	if (ft_strchr(settings->flags, '0') && ft_strchr("+- ", *nb_to_print))
		add_padding(&nb_to_print, settings->width - 1);
	else if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	add_padding(&nb_to_print, settings->precision);
	print_left_right(settings, nb_to_print);
	free(nb_to_print);
}
