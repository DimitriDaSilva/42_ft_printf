/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 19:53:42 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/24 21:54:17 by dda-silv         ###   ########.fr       */
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
	get_exp_str(&nb, &exponent);
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

void	print_g(t_format *settings)
{
	double	nb;
	int		exponent;
	int		actual_precision;
	
	nb = va_arg(g_arg_list, double);
	exponent = get_exp_nb(nb);
	actual_precision = settings->precision <= -1 ? 6 : settings->precision;
	if (settings->precision == 0)
		actual_precision  = 1;
	if (-4 <= exponent && exponent < actual_precision)
		print_g_flt(settings, nb, actual_precision - 1 - exponent);
	else
		print_g_exp(settings, nb, actual_precision - 1);
}

void	print_g_flt(t_format *settings, double nb, int precision)
{
	char	*nb_to_print;

	if (0.9 < ft_abs_dl(nb) && ft_abs_dl(nb) < 1)
		precision++;
	nb_to_print = ft_ftoa(nb, precision);
	if (!ft_strchr(settings->flags, '#'))
		remove_trailing_zero(nb_to_print);
	add_point(&nb_to_print, settings);
	add_sign(&nb_to_print, settings->flags);
	if (ft_strchr(settings->flags, '0') && ft_strchr("+- ", *nb_to_print))
		add_padding(&nb_to_print, settings->width - 1);
	else if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	print_left_right(settings, nb_to_print);
	free(nb_to_print);
}

void	print_g_exp(t_format *settings, double nb, int precision)
{
	(void)settings;
	(void)nb;
	(void)precision;
	ft_printf("%%e");
	return ;
}
