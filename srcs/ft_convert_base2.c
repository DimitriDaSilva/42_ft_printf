/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:21:09 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/19 10:38:59 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_custom_strchr(char *str, char to_find)
{
	char *sav_s;

	sav_s = str;
	while (*str)
	{
		if (*str == to_find)
			return (str - sav_s);
		str++;
	}
	return (-1);
}
