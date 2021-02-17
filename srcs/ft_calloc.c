/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:25:20 by dda-silv          #+#    #+#             */
/*   Updated: 2021/02/16 09:54:57 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	mem = 0;
	if (size == 0)
		return (ft_strdup(""));
	if (nmemb == 0)
		return (0);
	if (!(mem = malloc(nmemb * size)))
		return (0);
	ft_memset(mem, 0, nmemb * size);
	return (mem);
}
