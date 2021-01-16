/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/16 22:40:34 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/libft.h"

int ft_printf(const char *s, ...)
{
	va_list	args;
	int		arg_count;
	
	arg_count = get_arg_count(s);
	va_start(args, arg_count);
	while (arg_count--)
	{
		va_arg(args, int);
	}
	va_end(args);
	return (0);
}

int	main(int argc, char *argv[])
{
	float division = (float)1/(float)3;
	printf("%*f\n", -10, division);
}