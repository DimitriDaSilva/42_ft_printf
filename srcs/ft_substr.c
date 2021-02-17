/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:46:58 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/16 10:34:55 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	s_len;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	if (s_len == 0)
		return (0);
	if (s_len <= start)
	{
		if (!(new_str = ft_calloc(1, sizeof(char))))
			return (0);
		*new_str = 0;
		return (new_str);
	}
	if (s_len < len)
		len = s_len;
	if (!(new_str = ft_calloc(len + 1, sizeof(char))))
		return (0);
	ft_strlcpy(new_str, s + start, len + 1);
	return (new_str);
}
