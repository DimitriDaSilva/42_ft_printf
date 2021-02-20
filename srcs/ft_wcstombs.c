/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcstombs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 17:39:08 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/20 10:42:25 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wcstombs(char *s, wchar_t *pwcs, size_t size)
{
	int		i;

	i = 0;
	while (size > 0)
	{
		s[i] = pwcs[i];
		i++;
		size--;
	}
	s[i] = '\0';
	return (i);
	// int	count;

	// count = 0;
	// while (count < (int)size)
	// {
	// 	*s = (char)*pwcs;
	// 	if (*s == 0)
	// 		break ;
	// 	s++;
	// 	pwcs++;
	// 	count++;
	// }
	// return (count);
	// int i = size;

	// while (--i >= 0)
	// {
	// 	if (!(*s++ = (unsigned char)*pwcs++))
	// 		break;
	// }
	// return size - i - 1;
}
