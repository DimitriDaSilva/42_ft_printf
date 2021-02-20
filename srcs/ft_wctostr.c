/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 12:16:17 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/20 19:47:01 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Useful resource for wide characters: https://en.wikipedia.org/wiki/UTF-8
*/

/*
** Converts a wide character to a string composed of single-byte characters
** The wide character is a binary number that we need to encode to UTF format.
** The UTF format can be composed of 1 to 4 bytes, depending where the binary
** lands in the hex ranges:
** - 1-byte UTF range: 0 to 7F
** - 2-byte UTF range: 80 to 7FF
** - 3-byte UTF range: 800 to FFFF
** - 4-byte UTF range: 10000 to 10FFFF
** The first byte of an UTF always has a distinctive code to let us know ahead
** of how many bytes we are going to find. All subsequent bytes have the same
** mask (10xxxxxx)
** Masks per types of UTF:
** - 1-byte UTF: 0xxx xxxx
** - 2-byte UTF: 110x xxxx | 10xx xxxx
** - 3-byte UTF: 1110 xxxx | 10xx xxxx | 10xx xxxx
** - 4-byte UTF: 1111 0xxx | 10xx xxxx | 10xx xxxx | 10xx xxxx
** So these masks will only be used to encode our code points. For example:
** - UTF U+00A2 which in HEX = C2 A2
** - In binary, here refered as code points:	000 1010 0010
** - After UTF-8 encoding:						[110]00010 [10]100010
** This means that, for a 2-bytes UTF, to get the code point of the first byte,
** we need to right-shift it 6 bits so that 000 1010 0010 becomes 000 10 (yes,
** the leading position is filled with zero in practice). The bit shifting
** executed down below is executed on binary
** @param:	- [char *] dest string
**			- [wchar_t] wide char to converted
**			- [size_t] length in chars of a wide char. Result of ft_wclen(wc)
** Line-by-line comments:
** @1		For 1-byte UTF - 7 code points:
** @2		The mask being 0xxxxxxx we know that the seven bits left represent
**			an ASCII value in binary format (ASCII non-extended because 7bits
**			allow us to write from 0 until only 127)
** @3		For 2-byte UTF - 11 code points:
** @5		1st char: we bit shift right by 6 to get the left-most 5 bits and we
**			mask it	with 110xxxxx (i.e. 0xC0)
** @6		2nd char: we keep the 6 remaining bits with AND operator with 3F
**			combined with the operand 3F (111111 in binary). After that, we
**			apply the 80 mask (10000000) with the OR operator
** @8		For 3-byte UTF - 16 code points:
** @10		1st char: we bit shift right by 12 to get the left-most 4 bits and we
**			mask it	with 1110xxxx (i.e. 0xE0)
** @11		2nd char: we need to right shift 6 bits to get the second byte. Then
**			exact same reasoning as in line 6
** @12		3rd: char: exact same reasoninng as in line 6
** @14		For 4-byte UTF - 21 code points:
** @16		1st char: we bit shift right by 16 to get the left-most 3 bits and we
**			mask it	with 11110xxx (i.e. 0xF0)
** @17		2nd: char: exact same reasoninng as in line 11
** @17		3rd: char: exact same reasoninng as in line 11
** @17		4th: char: exact same reasoninng as in line 6
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
