/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrcolornl_c.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 17:52:29 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/05 14:02:48 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbrcolornl(int nb, char *color)
{
	ft_putstr(color);
	ft_putnbr(nb);
	ft_putstr("\033[0m\n");
}
