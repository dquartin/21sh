/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:56:51 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/25 16:17:59 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstrerror(char *s)
{
	ft_putstr(LIGHT_RED);
	write(2, s, ft_strlen(s));
	ft_putstr("\033[0m");
}

int			ft_puterror(char *s)
{
	ft_putstr(LIGHT_RED);
	write(2, s, ft_strlen(s));
	ft_putendl("\033[0m");
	return (0);
}
