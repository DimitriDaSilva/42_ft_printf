/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:40:11 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/22 13:34:21 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_TYPES_H
# define FT_PRINTF_TYPES_H

# include "ft_printf.h"

int	print(t_format *settings);
int	print_char(t_format *settings);
int	print_str(t_format *settings);
int	print_ptr(t_format *settings);
int	print_int(t_format *settings);
int	print_hex(t_format *settings);
int	print_pct(t_format *settings);
int	print_flt(t_format *settings);
int	print_left_right(char *str, t_format *settings);

#endif
