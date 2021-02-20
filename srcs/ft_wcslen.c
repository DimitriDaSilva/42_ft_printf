/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcslen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 20:02:54 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/19 20:05:44 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcslen(wchar_t *s)
{
	size_t len;

	len = 0;
	while (s[len] != L'\0')
	{
		if (s[++len] == L'\0')
			return len;
		if (s[++len] == L'\0')
			return len;
		if (s[++len] == L'\0')
			return len;
		++len;
	}
	return (len);
}