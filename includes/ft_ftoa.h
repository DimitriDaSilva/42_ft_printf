/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 08:32:33 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/22 13:38:06 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FTOA_H
# define FT_FTOA_H

# include "libft.h"

static char		*ft_round(double nb, int length, char *str_nb);
static double	ft_remainder(double numer, double denom);
static char		*increment(char *str_nb, int length);
static int		get_new_length(char *str_nb, int length);

#endif
