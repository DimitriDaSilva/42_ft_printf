/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/20 09:27:59 by dda-silv         ###   ########.fr       */
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
** 
** @param:	- []
**  		- [] 
** @return: [] 
** Line-by-line comments:
** @#-#		
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
** 
** @param:	- []
**  		- [] 
** @return: [] 
** Line-by-line comments:
** @#-#		
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
** 
** @param:	- []
**  		- [] 
** @return: [] 
** Line-by-line comments:
** @#-#		
*/

int	print_int(t_format *settings)
{
	int		nb_printed_chars;
	char	*nb_to_print;

	if (settings->type == 'd' || settings->type == 'i')
		nb_to_print = ft_itoa(va_arg(g_arg_list, int));
	else if (settings->type == 'u')
		nb_to_print = ft_itoa(va_arg(g_arg_list, unsigned int));
	if (settings->precision == 0 && *nb_to_print == '0')
		*nb_to_print = ' ';
	else
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
