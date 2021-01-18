/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 18:46:57 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/18 23:12:13 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	char *saved;

	saved = dest;
	while ((*dest++ = *src++) != '\0')
		;
	return (saved);
}

char		*ft_strdup(const char *s)
{
	int		s_len;
	char	*cpy;

	if (!s)
	{
		if (!(cpy = malloc(1)))
			return (0);
		*cpy = 0;
		return (cpy);
	}
	s_len = ft_strlen(s) + 1;
	if (!(cpy = malloc(s_len * sizeof(char))))
		return (0);
	ft_strcpy(cpy, s);
	return (cpy);
}
