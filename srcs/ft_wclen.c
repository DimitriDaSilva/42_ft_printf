/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wclen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 19:47:25 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/20 19:47:26 by dda-silv         ###   ########.fr       */
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
** @1-2		Largest a 1-byte UTF can be is 0x7F
** @3-4		Largest a 2-byte UTF can be is 0x07FF
** @5-6		Largest a 3-byte UTF can be is 0xFFFF
** @7-8		Largest a 4-byte UTF can be is 0x10FFFF
*/

size_t	ft_wclen(wchar_t wc)
{
	if (wc <= 0x7F)
		return (1);
	else if (wc <= 0x07FF)
		return (2);
	else if (wc <= 0xFFFF)
		return (3);
	else if (wc <= 0x10FFFF)
		return (4);
	return (0);
}
