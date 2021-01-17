/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/17 23:01:14 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert(const char **fmt, va_list arg_list);
static int	convert_type(const char **fmt, va_list arg_list);
static int	convert_type_alpha(const char **fmt, va_list arg_list);
static int	convert_type_ptr(const char **fmt, va_list arg_list);
static int	convert_type_int(const char **fmt, va_list arg_list);
static int	convert_type_hex(const char **fmt, va_list arg_list);

int			ft_printf(const char *fmt, ...)
{
	va_list	arg_list;
	int		nb_printed_chars;
	
	nb_printed_chars = 0;
	va_start(arg_list, fmt);
	while (*fmt)
	{
		if (!ft_strncmp(fmt, "%%", 1))
		{
			fmt++;
			nb_printed_chars += convert(&fmt, arg_list);
		}
		else
		{
			nb_printed_chars++;
			write(1, fmt, 1);
		}
		fmt++;
	}
	va_end(arg_list);
	return (nb_printed_chars);
}

/*
** This function is called when a % is detected.
** Return value: number of printed characters
*/

static int	convert(const char **fmt, va_list arg_list)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	// convert_flags()
	nb_printed_chars += convert_type(fmt, arg_list);
	// ft_putnbr(va_arg(arg_list, int));

	// (*fmt)++;
	return (nb_printed_chars);
}

static int	convert_type(const char **fmt, va_list arg_list)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (ft_strchr("cs", **fmt))
		nb_printed_chars = convert_type_alpha(fmt, arg_list);
	else if (**fmt == 'p')
		nb_printed_chars = convert_type_ptr(fmt, arg_list);
	else if (ft_strchr("diu", **fmt))
		nb_printed_chars = convert_type_int(fmt, arg_list);
	else if (ft_strchr("pxX", **fmt))
		nb_printed_chars = convert_type_hex(fmt, arg_list);
	else if (**fmt == '%')
		nb_printed_chars = ft_putchar('%');
	else
	{
		ft_putstr("\n/!\\ Support for %");
		ft_putchar(**fmt);
		ft_putstr(" specifier not yet implemented /!\\\n");
	}
	return (nb_printed_chars);
}

static int	convert_type_alpha(const char **fmt, va_list arg_list)
{
	int		nb_printed_chars;

	if (**fmt == 'c')
		nb_printed_chars = ft_putchar(va_arg(arg_list, int));
	else
		nb_printed_chars = ft_putstr(va_arg(arg_list, char *));
	return (nb_printed_chars);
}

static int	convert_type_ptr(const char **fmt, va_list arg_list)
{
	long long	nb_to_convert;
	(void)fmt;

	nb_to_convert = va_arg(arg_list, long long);
	ft_putstr("0x");
	ft_putnbr_base(nb_to_convert, "0123456789abcdef");
	return (14);
}

static int	convert_type_int(const char **fmt, va_list arg_list)
{
	int		nb_printed_chars;

	if (**fmt == 'd' || **fmt == 'i')
		nb_printed_chars = ft_putstr(ft_itoa(va_arg(arg_list, int)));
	else
		nb_printed_chars = ft_putstr(ft_itoa(va_arg(arg_list, unsigned int)));
	return (nb_printed_chars);
}

static int	convert_type_hex(const char **fmt, va_list arg_list)
{
	int		nb_to_convert;

	nb_to_convert = va_arg(arg_list, int);
	if (**fmt == 'x')
		ft_putnbr_base(nb_to_convert, "0123456789abcdef");
	else if (**fmt == 'X')
		ft_putnbr_base(nb_to_convert, "0123456789ABCDEF");
	return (nb_to_convert >= 16 ? 2 : 1);
}

// int	main(int argc, char *argv[])
// {
// 	(void)argc;
// 	(void)argv;
// 	// int retMine = 0;
// 	int retOrig = 0;
// 	// Testing for char
// 	// retMine = ft_printf("I'm %c yo\n", -5);
// 	// retOrig = printf("I'm %c yo\n", -5);

// 	// Testing for char *
// 	// retMine = ft_printf("I'm %s yo\n", "twenty-five");
// 	// retOrig = printf("I'm %s yo\n", "twenty-five");

// 	// Testing for hex
// 	// retMine = ft_printf("Hexadecimal integers: %x\n", 30);
// 	// retOrig = printf("Hexadecimal integers: %x\n", 30);

// 	// Testing for pointer
// 	// retMine = ft_printf("RetMine's address: %p\n", &retMine);
// 	// retOrig = printf("RetMine's address: %p\n", &retMine);

// 	// Testing for int d
// 	// retMine = ft_printf("I'm %d yo\n", 25);
// 	retOrig = printf("I'm %i yo\n", 25);

// 	// Testing for int i
// 	// retMine = ft_printf("I'm %i yo\n", 25);
// 	// retOrig = printf("I'm %i yo\n", 25);

// 	// Testing for int u
// 	// retMine = ft_printf("I'm %u yo\n", -25);
// 	// retOrig = printf("I'm %u yo\n", -25);

// 	// Testing for %
// 	// retMine = ft_printf("Percentage sign: %%\n");
// 	// retOrig = printf("Percentage sign: %%\n");

// 	// Testing for several types at once
// 	// retMine = ft_printf("I'm %s\nI'm %d yo\n%c\n", "Dimitri", 25, 'd');
// 	// retOrig = printf("I'm %s\nI'm %d yo\n%c\n", "Dimitri", 25, 'd');

// 	// Testing for non implemented specifiers
// 	// retMine = ft_printf("Float: %f\n", 4.5);
// 	// retOrig = printf("Float: %f\n", 4.5);

// 	// printf("RetMine: %d\n", retMine);
// 	printf("RetOrig: %d\n", retOrig);
// }