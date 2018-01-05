/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:34:13 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/02 15:36:05 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_padding(int nb, int space)
{
	int i;

	i = 0;
	while (i + ft_nbdigit(nb, 10) < space)
	{
		ft_putchar(' ');
		i++;
	}
	ft_putnbr(nb);
}
