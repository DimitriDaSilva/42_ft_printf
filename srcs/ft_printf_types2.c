/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/20 09:28:17 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_types.h"

/*
** 
** @param:	- []
**  		- [] 
** @return: [] 
** Line-by-line comments:
** @#-#		
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
	if (settings->precision == 0 && *str_to_print == '0')
		*str_to_print = ' ';
	else
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
** 
** @param:	- []
**  		- [] 
** @return: [] 
** Line-by-line comments:
** @#-#		
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
** 
** @param:	- []
**  		- [] 
** @return: [] 
** Line-by-line comments:
** @#-#		
*/

int	print_left(char *str, t_format *settings, char padding)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (settings->type == 'p')
		nb_printed_chars += ft_putstr("0x");
	if (settings->type == 'c' && *str == 0)
		nb_printed_chars += ft_putchar(0);
	else if (!ft_strchr("duixX", settings->type) || !(*str == ' '))
		nb_printed_chars += ft_putstr(str);
	settings->width -= nb_printed_chars;
	while (settings->width-- > 0)
		nb_printed_chars += ft_putchar(padding);
	return (nb_printed_chars);
}

/*
** 
** @param:	- []
**  		- [] 
** @return: [] 
** Line-by-line comments:
** @#-#		
*/

int	print_right(char *str, t_format *settings, char padding)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (*str == '-' && padding == '0')
		nb_printed_chars += ft_putchar(*str++);
	if (settings->type == 'c' && *str == 0)
		settings->width--;
	else if (ft_strchr("duixX", settings->type) && *str == ' ')
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
	else if (!ft_strchr("duixX", settings->type) || !(*str == ' '))
		nb_printed_chars += ft_putstr(str);
	return (nb_printed_chars);
}
