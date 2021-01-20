/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:40:11 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/20 15:40:31 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

typedef struct	s_format
{
	char		flags[2];
	int			width;
	int			precision;
	char		size[2];
	char		type;
}				t_format;

# include "libft.h"
# include "ft_printf_types.h"
# include "ft_printf_utils.h"


va_list			g_arg_list;

int		convert(const char **fmt);
void 	get_settings(const char **fmt, t_format *settings);

#endif
