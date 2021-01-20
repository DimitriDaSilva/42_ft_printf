/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/20 15:40:43 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Adds 0 at the left of ints when precision is higher than length of int
** @param:	- [char **nbr] 	Number in a str format. Ptr to a ptr because we
** 							need to free and allocate more space
**  		- [int precision] Number passed after the . in the format. For
** 							ints, the precision defines the length of
** 								the number. If precision > length of the int,
** 								then we add add 0 to the left of the int
** @return: [void] The value is passed through the pointer **get_size_nbr
** Line-by-line comments:
** @10-12	Check if precision > nbr. The '-' doesn't count so we need to
**			make a specific use case for it. If not, return.
** @13		The length of the new_nb depends on the sign
** @16-17	The '-' sign needs to go before the padding of 0s
*/

void	add_padding(char **nb, int precision)
{
	int		length_old_nb;
	int		length_new_nb;
	char	*tmp_new_nb;
	int		i;
	int		j;

	i = 0;
	j = 0;
	length_old_nb = (int)ft_strlen(*nb);
	if (((*nb)[i] == '-' && length_old_nb - 1 >= precision) ||
		((*nb)[i] != '-' && length_old_nb >= precision))
		return ;
	length_new_nb = (*nb)[i] == '-' ? precision + 2 : precision;
	if (!(tmp_new_nb = calloc(length_new_nb + 1, sizeof(char))))
		return ;
	if ((*nb)[i] == '-' && length_new_nb--)
		tmp_new_nb[j++] = (*nb)[i++];
	while (length_new_nb-- > length_old_nb)
		tmp_new_nb[j++] = '0';
	while (length_new_nb-- != -1)
		tmp_new_nb[j++] = (*nb)[i++];
	free(*nb);
	*nb = tmp_new_nb;
}
