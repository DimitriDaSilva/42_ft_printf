/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/19 08:44:53 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert(const char **fmt);
static void	get_flags(const char **fmt, char *flags);
static int	get_width(const char **fmt);
static int	get_precision(const char **fmt);
static int	convert_type(const char **fmt, char *flags, int width, int precision);
static int	convert_type_alpha(const char **fmt, char *flags, int width, int precision);
static int	convert_type_ptr(const char **fmt, char *flags, int width, int precision);
static int	convert_type_int(const char **fmt, char *flags, int width, int precision);
static int	convert_type_hex(const char **fmt, char *flags, int width, int precision);
static int	convert_type_percent(const char **fmt, char *flags, int width, int precision);
static int	print_left(char *str, int width, char padding, char type);
static int	print_right(char *str, int width, char padding, char type);
static int	get_size_nbr(int n);

va_list	g_arg_list;

int			ft_printf(const char *fmt, ...)
{
	int		nb_printed_chars;
	
	nb_printed_chars = 0;
	va_start(g_arg_list, fmt);
	while (*fmt)
	{
		if (!ft_strncmp(fmt, "%%", 1))
		{
			fmt++;
			nb_printed_chars += convert(&fmt);
		}
		else
		{
			nb_printed_chars++;
			write(1, fmt, 1);
		}
		fmt++;
	}
	va_end(g_arg_list);
	return (nb_printed_chars);
}

/*
** This function is called when a % is detected.
** Return value: number of printed characters
*/

static int	convert(const char **fmt)
{
	int		nb_printed_chars;
	char	flags[2];
	int		width;
	int		precision;

	nb_printed_chars = 0;
	get_flags(fmt, flags);
	width = get_width(fmt);
	precision = get_precision(fmt);
	nb_printed_chars += convert_type(fmt, flags, width, precision);
	return (nb_printed_chars);
}

static void	get_flags(const char **fmt, char *flags)
{
	if ((**fmt == '-' && *(*fmt + 1) == '0') ||
			(**fmt == '0' && *(*fmt + 1) == '-'))
	{
		flags[0] = '\0';
		*fmt += 2;
	}
	else if ((**fmt == '-' && *(*fmt + 1) == '-') ||
			(**fmt == '0' && *(*fmt + 1) == '0'))
	{
		flags[0] = '\0';
		*fmt += 2;
	}
	else if (**fmt == '0' || **fmt == '-')
	{
		flags[0] = **fmt;
		(*fmt)++;
	}
	else
		flags[0] = '\0';
}

static int	get_width(const char **fmt)
{
	int	width;

	width = 0;
	if (**fmt == '*')
	{
		(*fmt)++;
		width = va_arg(g_arg_list, int);
	}
	else if (ft_isdigit(**fmt))
	{
		width = ft_atoi(*fmt);
		(*fmt) += get_size_nbr(width);
	}
	return (width);
}

static int	get_precision(const char **fmt)
{
	int	precision;

	precision = -1;
	if (**fmt == '.')
	{
		(*fmt)++;
		if (!ft_isdigit(**fmt))
			return (0);
		else
		{
			while (**fmt == '0')
				(*fmt)++;
			if (!ft_isdigit(**fmt))
				return (0);
			precision = ft_atoi(*fmt);
			(*fmt) += get_size_nbr(precision);
		}
	}
	return (precision);
}

static int	convert_type(const char **fmt, char *flags, int width, int precision)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (ft_strchr("cs", **fmt))
		nb_printed_chars = convert_type_alpha(fmt, flags, width, precision);
	else if (**fmt == 'p')
		nb_printed_chars = convert_type_ptr(fmt, flags, width, precision);
	else if (ft_strchr("diu", **fmt))
		nb_printed_chars = convert_type_int(fmt, flags, width, precision);
	else if (ft_strchr("pxX", **fmt))
		nb_printed_chars = convert_type_hex(fmt, flags, width, precision);
	else if (**fmt == '%')
		nb_printed_chars = convert_type_percent(fmt, flags, width, precision);
	return (nb_printed_chars);
}

static int	convert_type_alpha(const char **fmt, char *flags, int width, int precision)
{
	int		nb_printed_chars;
	char	*str;

	if (**fmt == 'c')
	{
		if (!(str = malloc(2 * sizeof(char))))
			return (0);
		str[0] = va_arg(g_arg_list, int);
		str[1] = '\0';
	}
	else
	{
		if (!(str = va_arg(g_arg_list, char *)))
			str = ft_strdup("(null)");
		else if (*str == 0)
			return (0);
		else
			str = ft_strdup(str);
		if (precision == 0)
		{
			fmt++;
			return (0);
		}
		else if (precision != -1 && precision < (int)ft_strlen(str))
			str[precision] = 0;
	}
	if (*flags == '-')
		nb_printed_chars = print_left(str, width, ' ', **fmt);
	else if (*flags == 0)
		nb_printed_chars = print_right(str, width, ' ', **fmt);
	free(str);
	return (nb_printed_chars);
}

static int	convert_type_ptr(const char **fmt, char *flags, int width, int precision)
{
	long long	nb_to_convert;
	int			nb_printed_chars;
	(void)fmt;
	(void)precision;

	nb_printed_chars = 14;
	nb_to_convert = va_arg(g_arg_list, long long);
	if (*flags == '-')
	{
		ft_putstr("0x");
		ft_putnbr_base(nb_to_convert, "0123456789abcdef");
		width -= nb_printed_chars;
		while (width-- > 0)
			nb_printed_chars += ft_putchar(' ');
	}
	else
	{
		width -= nb_printed_chars;
		while (width-- > 0)
			nb_printed_chars += ft_putchar(' ');
		ft_putstr("0x");
		ft_putnbr_base(nb_to_convert, "0123456789abcdef");
	}
	return (nb_printed_chars);
}

static int	convert_type_int(const char **fmt, char *flags, int width, int precision)
{
	int		nb_printed_chars;
	char	*nb_to_print;
	(void)precision;

	if (**fmt == 'd' || **fmt == 'i')
		nb_to_print = ft_itoa(va_arg(g_arg_list, int));
	else if (**fmt == 'u')
		nb_to_print = ft_itoa(va_arg(g_arg_list, unsigned int));
	if (*flags == '-')
		nb_printed_chars = print_left(nb_to_print, width, ' ', **fmt);
	else if (*flags == '0')
		 nb_printed_chars = print_right(nb_to_print, width, '0', **fmt);
	else
		nb_printed_chars = print_right(nb_to_print, width, ' ', **fmt);
	free(nb_to_print);
	return (nb_printed_chars);
}

static int	convert_type_hex(const char **fmt, char *flags, int width, int precision)
{
	int		nb_to_convert;
	int		nb_printed_chars;
	char	base[17];
	(void)precision;

	nb_to_convert = va_arg(g_arg_list, int);
	nb_printed_chars = nb_to_convert >= 16 ? 2 : 1;
	if (**fmt == 'x')
		ft_strlcpy(base, "0123456789abcdef", 17);
	else
		ft_strlcpy(base, "0123456789ABCDEF", 17);
	if (*flags == '-')
	{
		ft_putnbr_base(nb_to_convert, base);
		width -= nb_printed_chars;
		while (width-- > 0)
			nb_printed_chars += ft_putchar(' ');
	}
	else
	{
		width -= nb_printed_chars;
		while (width-- > 0)
			nb_printed_chars += ft_putchar(' ');
		ft_putnbr_base(nb_to_convert, base);
	}
	return (nb_printed_chars);
}

static int	convert_type_percent(const char **fmt, char *flags, int width, int precision)
{
	int		nb_printed_chars;
	(void)fmt;
	(void)width;
	(void)precision;

	nb_printed_chars = 0;
	if (*flags == '-')
		nb_printed_chars = print_left("%", 0, ' ', '%');
	else if (*flags == '0')
		 nb_printed_chars = print_right("%", 0, '0', '%');
	else
		nb_printed_chars = print_right("%", 0, ' ', '%');
	return (nb_printed_chars);
}

static int	print_left(char *str, int width, char padding, char type)
{
	int		nb_printed_chars;

	if (type == 'c' && *str == 0)
		nb_printed_chars = ft_putchar(0);
	else if (type == 's' && *str == 0)
		nb_printed_chars = ft_putstr("(null)");
	else
		nb_printed_chars = ft_putstr(str);
	width -= nb_printed_chars;
	while (width-- > 0)
		nb_printed_chars += ft_putchar(padding);
	return (nb_printed_chars);
}

static int	print_right(char *str, int width, char padding, char type)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (*str == '-' && padding == '0')
		nb_printed_chars += ft_putchar(*str++);
	width -= *str ? ft_strlen(str) : 1;
	while (width-- > 0)
		nb_printed_chars += ft_putchar(padding);
	if (type == 'c' && *str == 0)
		nb_printed_chars += ft_putchar(0);
	else if (type == 's' && *str == 0)
		nb_printed_chars += ft_putstr("(null)");
	else
		nb_printed_chars += ft_putstr(str);
	return (nb_printed_chars);
}

static int	get_size_nbr(int n)
{
	if (0 <= n && n < 10)
		return (1);
	else if (-10 < n && n < 0)
		return (2);
	return (1 + get_size_nbr(n / 10));
}

// int	main(int argc, char *argv[])
// {
// 	(void)argc;
// 	(void)argv;
// 	int retMine = 0;
// 	int retOrig = 0;

// 	// Testing for char
// 	// retMine = ft_printf("I'm %c yo\n", '\0');
// 	// retOrig = printf("I'm %c yo\n", '\0');

// 	// Testing for char *
// 	retMine = ft_printf("hello, %s.\n", 0);
// 	// retOrig = printf("hello, %s.", NULL);

// 	// Testing for hex
// 	// retMine = ft_printf("Hexadecimal integers: %-5x\n", 30);
// 	// retOrig = printf("Hexadecimal integers: %-5x\n", 30);

// 	// Testing for pointer
// 	// retMine = ft_printf("RetMine's address: %025p\n", &retMine);
// 	// retOrig = printf("RetMine's address: %-*p\n", 25, &retMine);

// 	// Testing for int d
// 	// retMine = ft_printf("I'm %5d yo\n", 25);
// 	// retOrig = printf("I'm %5d yo\n", 25);

// 	// Testing for int i
// 	// retMine = ft_printf("I'm %i yo\n", 25);
// 	// retOrig = printf("I'm %i yo\n", 25);

// 	// Testing for int u
// 	// retMine = ft_printf("I'm %u yo\n", 25);
// 	// retOrig = printf("I'm %u yo\n", 25);

// 	// Testing for %
// 	// retMine = ft_printf("Percentage sign: %5%\n");
// 	// retOrig = printf("Percentage sign: %5%\n");

// 	// Testing for several types at once
// 	// retMine = ft_printf("I'm %s\nI'm %d yo\n%c\n", "Dimitri", 25, 'd');
// 	// retOrig = printf("I'm %s\nI'm %d yo\n%c\n", "Dimitri", 25, 'd');

// 	// Testing for non implemented specifiers
// 	// retMine = ft_printf("Float: %f\n", 4.5);
// 	// retOrig = printf("Float: %f\n", 4.5);

// 	// Testing for flags - and 0
// 	// retMine = ft_printf("I'm %i yo\n", 25);
// 	// retOrig = printf("I'm %55i yo\n", 25);

// 	// Testing for width
// 	// retMine = ft_printf("I'm %010i yo\n", -25);
// 	// retOrig = printf("I'm %014f yo\n", -25.5);

// 	// Testing for precision
// 	// retMine = ft_printf("I'm %.5555555i yo\n", 25);
// 	// retOrig = printf("I'm %.5i yo\n", 25);

// 	// Testing for floats
// 	// retMine = ft_printf("I'm %.4f yo\n", 2.718281828);
// 	// retOrig = printf("I'm %.2f yo\n", 2.715844448);

// 	// Weird use case that outputs "I'm 00025 yo"
// 	// retOrig = printf("I'm %-5.5i yo\n", 25);


// 	printf("RetMine: %d\n", retMine);
// 	printf("RetOrig: %d\n", retOrig);
// }