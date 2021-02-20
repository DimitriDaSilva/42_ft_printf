/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:16:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/20 13:35:53 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Useful resource for wide characters: https://en.wikipedia.org/wiki/UTF-8
*/

/*
** Converts a wide characters to a string composed of single-byte characters
** @param:	- [char *] dest string
**			- [wchar_t] wide char to converted
**			- [size_t] length in chars of a wide char. Result of ft_wcharlen(wc)
** Line-by-line comments:
** @1-2		For single-byte char, we can directly copy wc
** @3		For dual-byte char:
** @5		We bit shift right by 6 to get the left-most 5 1's and we mask it
**			with 110xxxxx (i.e. 0xC0)
** @6		We take the 6 remaining 1's us
**	For 1 byte UTF the mask looks like 0xxxxxxx
**	For 2 byte UTF the mask looks like 110xxxxx for 1st byte then 10xxxxxx
**	for all subsequent bytes
**	For 3 byte UTF the mask looks like 1110xxxx for 1st byte then 10xxxxxx
**	for all subsequent bytes
**	For 4 byte UTF the mask looks like 11110xxx for 1st byte then 10xxxxxx
**	for all subsequent bytes
**
**	For stuff <= 0x7F (01111111) we can just directly write it out.
**
**	For stuff <= 0x07FF (11111111111) we bit shift right by 6 to get the left-
**	most 5 1's (11111) and we 'OR' it with (110xxxxx) == (0xC0). We then take
**	the remaining 6 1's (111111) using (0x3F) == (111111) as a mask and
**	'OR' it with (0x80) == (10000000).
**
**	We continue in a similar manner but use the appropriate mask for the first
**	byte (i.e. 0, 0xC0, 0xE0, 0xF0).
*/

void	ft_wctostr(char *s, wchar_t wc, size_t wc_len)
{
	if (wc_len == 1)
		*s = wc;
	else if (wc_len == 2)
	{
		*s++ = (wc >> 6) | 0xC0;
		*s++ = (wc & 0x3F) | 0x80;
	}
	else if (wc_len == 3)
	{
		*s++ = (wc >> 12) | 0xE0;
		*s++ = ((wc >> 6) & 0x3F) | 0x80;
		*s++ = (wc & 0x3F) | 0x80;
	}
	else if (wc_len == 4)
	{
		*s++ = (wc >> 18) | 0xF0;
		*s++ = ((wc >> 12) & 0x3F) | 0x80;
		*s++ = ((wc >> 6) & 0x3F) | 0x80;
		*s++ = (wc & 0x3F) | 0x80;
	}
}
