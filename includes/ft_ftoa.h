/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:32:33 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/21 19:18:21 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FTOA_H
# define FT_FTOA_H

# include "libft.h"

static void		ft_round(double nb, int length, char *str_nb, int precision);
static double	ft_remainder(double numer, double denom);
static int		ft_is_even(int c);

#endif