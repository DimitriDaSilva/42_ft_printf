/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_settings.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 08:40:11 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/20 15:26:27 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_SETTINGS_H
# define FT_PRINTF_SETTINGS_H

# include "ft_printf.h"

static char	*get_flags(const char **fmt);
static int	get_width(const char **fmt);
static int	get_precision(const char **fmt);
static char	*get_size(const char **fmt);

#endif
