/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 11:05:48 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/09 11:27:07 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_cmpt(unsigned int nb, int len)
{
	int		cmpt;

	cmpt = 0;
	while (nb != 0)
	{
		cmpt++;
		nb = nb / len;
	}
	return (cmpt);
}

char			*ft_itoa_base(unsigned int nb, char *base)
{
	char	*str;
	int		i;
	int		res;

	res = ft_cmpt(nb, ft_strlen(base));
	i = res - 1;
	if (!(str = ft_strnew(res)))
		return (NULL);
	if (nb == 0)
		str[0] = base[0];
	while (nb != 0)
	{
		str[i] = base[nb % ft_strlen(base)];
		nb = nb / ft_strlen(base);
		i--;
	}
	str[res] = '\0';
	return (str);
}
