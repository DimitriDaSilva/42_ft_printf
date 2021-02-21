/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 18:52:55 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/21 11:02:43 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	static double			mx_f = -56.2012685;
	static long				mx_li =  4223372036854775800;
	static long long		mx_lli = 3223372036654775200;
	static short			mx_hi = -3244;
	static char				mx_hhi = 'F';
	static unsigned int		mx_u = 235;
	static char				mx_c = 'G';
	static char			   *mx_s = "Hello, World!";
	static int				mx_i = 42;


	// Bugs not fixed
	// printf("Orig: % -10.*e \n", 42, -1.);
	ft_printf("Mine: % -010.*e \n", 42, -1.);


	(void)argc;
	(void)argv;
	(void)mx_f;
	(void)mx_li;
	(void)mx_lli;
	(void)mx_hi;
	(void)mx_hhi;
	(void)mx_u;
	(void)mx_c;
	(void)mx_s;
	(void)mx_i;
	return (0);
}