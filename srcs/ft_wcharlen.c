/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:51:26 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/20 13:22:19 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Useful resource for wide characters: https://en.wikipedia.org/wiki/UTF-8
*/

/*
** Get length of a wide char
** @param:	- [wchar_t] wide char
** @return:	[size_t] size of the wide char (from 1 to 4 bytes)
** Line-by-line comments:
** @1-2		Largest a single width wide char can be 0x007F
** @3-4		Largest a double width wide char can be 0x07FF
** @5-6		Largest a triple width wide char can be 0xFFFF
** @7-8		Largest a quad width wide char can be 0x10FFFF
*/

size_t	ft_wcharlen(wchar_t wc)
{
	if (wc <= 0x007F)
		return (1);
	else if (wc <= 0x07FF)
		return (2);
	else if (wc <= 0xFFFF)
		return (3);
	else if (wc <= 0x10FFFF)
		return (4);
	return (0);
}
