/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:02:54 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/20 13:22:13 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Useful resource for wide characters: https://en.wikipedia.org/wiki/UTF-8
*/

/*
** Get length of wide char string
** @param:	- [wchar_t *] wide char string
** @return:	[size_t] length of the wide char string
** Line-by-line comments:
** @7		Each char can have a variable size (from 1 to 4 bytes)
*/

size_t	ft_wstrlen(wchar_t *wstr)
{
	size_t	wlen;

	wlen = 0;
	while (*wstr != L'\0')
	{
		wlen += ft_wcharlen(*wstr);
		wstr++;
	}
	return (wlen);
}
