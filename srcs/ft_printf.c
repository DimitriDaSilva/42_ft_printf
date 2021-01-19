/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/19 23:40:55 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

typedef struct	s_format
{
	char		flags[2];
	int			width;
	int			precision;
	char		size[2];
	char		type;
}				t_format;

static int	convert(const char **fmt);
static void get_settings(const char **fmt, t_format *settings);
static char	*get_flags(const char **fmt);
static int	get_width(const char **fmt);
static int	get_precision(const char **fmt);
static char	*get_size(const char **fmt);
static int	print(const char **fmt, t_format *settings);
static int	print_char(const char **fmt, t_format *settings);
static int	print_str(const char **fmt, t_format *settings);
static int	print_ptr(const char **fmt, t_format *settings);
static int	print_int(const char **fmt, t_format *settings);
static int	print_hex(const char **fmt, t_format *settings);
static int	print_pct(const char **fmt, t_format *settings);
static int	print_left(char *str, t_format *settings, char padding);
static int	print_right(char *str, t_format *settings, char padding);
static int	get_size_nbr(int n);
static void add_padding(char **nb, int precision);

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

static int	convert(const char **fmt)
{
	int			nb_printed_chars;
	t_format	settings;

	nb_printed_chars = 0;
	get_settings(fmt, &settings);
	nb_printed_chars = print(fmt, &settings);
	return (nb_printed_chars);
}

static void get_settings(const char **fmt, t_format *settings)
{
	settings->flags = get_flags(fmt);
	settings->width = get_width(fmt);
	settings->precision = get_precision(fmt);
	settings->size = get_size(fmt);
	settings->type = **fmt;
	if (settings->width < 0)
	{
		settings->flags[0] = '-';
		settings->width = ft_abs(settings->width);
	}
}

static char	*get_flags(const char **fmt)
{
	char	flags[2];

	if ((**fmt == '-' && *(*fmt + 1) == '-') ||
			(**fmt == '0' && *(*fmt + 1) == '0'))
	{
		flags[0] = '\0';
		*fmt += 2;
	}
	else if ((**fmt == '-' && *(*fmt + 1) == '0') ||
		(**fmt == '0' && *(*fmt + 1) == '-'))
	{
		flags[0] = '-';
		*fmt += 2;
	}
	else if (**fmt == '0' || **fmt == '-')
	{
		flags[0] = **fmt;
		(*fmt)++;
	}
	else
		flags[0] = '\0';
	flags[1] = '\0';
	return (flags);
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
	if (**fmt != '.')
		return (precision);
	if ((*fmt)++ && **fmt == '*')
	{
		(*fmt)++;
		precision = va_arg(g_arg_list, int);
	}
	else
	{
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

// To do 
static char	*get_size(const char **fmt)
{
	char size[2];

	(*fmt)++;
	size[0] = 'l';
	return (size);
}

static int	print(const char **fmt, t_format *settings)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if ('c' == settings->type)
		nb_printed_chars = print_char(fmt, settings);
	else if ('s' == settings->type)
		nb_printed_chars = print_str(fmt, settings);
	else if ('p' == settings->type)
		nb_printed_chars = print_ptr(fmt, settings);
	else if (ft_strchr("diu", settings->type))
		nb_printed_chars = print_int(fmt, settings);
	else if (ft_strchr("pxX", settings->type))
		nb_printed_chars = print_hex(fmt, settings);
	else if ('%' == settings->type)
		nb_printed_chars = print_pct(fmt, settings);
	return (nb_printed_chars);
}

static int	print_char(const char **fmt, t_format *settings)
{
	int		nb_printed_chars;
	char	*str;

	if (!(str = malloc(2 * sizeof(char))))
		return (0);
	str[0] = va_arg(g_arg_list, int);
	str[1] = '\0';
	if (settings->flags[0] == '-')
		nb_printed_chars = print_left(str, settings, ' ');
	else if (settings->flags[0] == 0)
		nb_printed_chars = print_right(str, settings, ' ');
	free(str);
	return (nb_printed_chars);
}

static int	print_str(const char **fmt, t_format *settings)
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
		str[precision] = 0;
	if (settings->flags[0] == '-')
		nb_printed_chars = print_left(str, settings, ' ');
	else if (settings->flags[0] == 0)
		nb_printed_chars = print_right(str, settings, ' ');
	free(str);
	return (nb_printed_chars);
}

static int	print_ptr(const char **fmt, t_format *settings)
{
	long long	nb_to_convert;
	int			nb_printed_chars;
	char		*str_to_print;
	(void)fmt;

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

static int	print_int(const char **fmt, t_format *settings)
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

static int	print_hex(const char **fmt, t_format *settings)
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

static int	print_pct(const char **fmt, t_format *settings)
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

// Potential improvement
	// else if (!ft_strchr("duixX", settings->type) || !*str == ' ')
	// 	nb_printed_chars += ft_putstr(str);
static int	print_left(char *str, t_format *settings, char padding)
{
	int		nb_printed_chars;

	nb_printed_chars = 0;
	if (settings->type == 'p')
		nb_printed_chars += ft_putstr("0x");
	if (settings->type == 'c' && *str == 0)
		nb_printed_chars += ft_putchar(0);
	else if (ft_strchr("duixX", settings->type) && *str == ' ')
		;
	else
		nb_printed_chars += ft_putstr(str);
	settings->width -= nb_printed_chars;
	while (settings->width-- > 0)
		nb_printed_chars += ft_putchar(padding);
	return (nb_printed_chars);
}

// Potential improvement
	// else if (!ft_strchr("duixX", settings->type) || !*str == ' ')
	// 	nb_printed_chars += ft_putstr(str);
static int	print_right(char *str, t_format *settings, char padding)
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
	else if (ft_strchr("duixX", settings->type) && *str == ' ')
		;
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

/*
** Adds 0 at the left of ints when precision is higher than length of int
** @param:	- [char **nbr] 	Number in a str format. Ptr to a ptr because we
** 							need to free and allocate more space
**  		- [int precision] Number passed after the . in the format. For
** 							ints, the precision defines the length of
** 								the number. If precision > length of the int,
** 								then we add add 0 to the left of the int
** @return: [void] The value is passed through the pointer **get_size_nbr
** Line-by-line comments:
** @10-12	Check if precision > nbr. The '-' doesn't count so we need to
**			make a specific use case for it. If not, return.
** @13		The length of the new_nb depends on the sign
** @16-17	The '-' sign needs to go before the padding of 0s 
*/

static void	add_padding(char **nb, int precision)
{
	int		length_old_nb;
	int		length_new_nb;
	char	*tmp_new_nb;
	int		i;
	int		j;

	i = 0;
	j = 0;
	length_old_nb = (int)ft_strlen(*nb);
	if (((*nb)[i] == '-' && length_old_nb - 1 >= precision) ||
		((*nb)[i] != '-' && length_old_nb >= precision))
		return ;
	length_new_nb = (*nb)[i] == '-' ? precision + 2 : precision;
	if (!(tmp_new_nb = malloc((length_new_nb + 1) * sizeof(char))))
		return ;
	if ((*nb)[i] == '-' && length_new_nb--)
		tmp_new_nb[j++] = (*nb)[i++];
	while (length_new_nb-- > length_old_nb)
		tmp_new_nb[j++] = '0';
	while (length_new_nb-- != -1)
		tmp_new_nb[j++] = (*nb)[i++];
	free(*nb);
	*nb = tmp_new_nb;
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
// 	// retMine = ft_printf("hello, %s.\n", 0);
// 	// retOrig = printf("hello, %s.", NULL);

// 	// Testing for hex
// 	// retMine = ft_printf("Hexadecimal integers: %-5x\n", 30);
// 	// retOrig = printf("Hexadecimal integers: %-5x\n", 30);

// 	// Testing for pointer
// 	retMine = ft_printf("RetMine's address: %5p\n", &retMine);
// 	retOrig = printf("RetMine's address: %p\n",&retMine);

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
// 	// int r00 = 0;
// 	// retMine = ft_printf("Lalalala, %d%% des gens qui parlent à Ly adorent %s. Ou Presque. %p\n", 100, "Ly", &r00);
// 	// retOrig = printf("Lalalala, %d%% des gens qui parlent à Ly adorent %s. Ou Presque. %p\n", 100, "Ly", &r00);

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