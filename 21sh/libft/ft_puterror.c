/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 18:56:51 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/08 17:38:34 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putstrerror(char *s)
{
	ft_putstr(LIGHT_RED);
	write(2, s, ft_strlen(s));
	ft_putstr("\033[0m");
}

void		ft_puterror(char *s)
{
	ft_putstr(LIGHT_RED);
	write(2, s, ft_strlen(s));
	ft_putendl("\033[0m");
}
