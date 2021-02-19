/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstombs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:39:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/19 18:07:01 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcstombs(char *s, wchar_t *pwcs, size_t size)
{
	// int	count;

	// count = 0;
	// while (count < (int)size)
	// {
	// 	// *s = (char)*pwcs;
	// 	// if (*s == 0)
	// 	// 	break ;
	// 	// s++;
	// 	// pwcs++;
	// 	// count++;
	// }
	int i = size;

	while (--i >= 0)
	{
		if (!(*s++ = (unsigned char)*pwcs++))
			break;
	}
	return size - i - 1;
}
