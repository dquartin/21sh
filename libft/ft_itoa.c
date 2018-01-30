/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 18:08:53 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/09 11:25:48 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_cmpt(int n)
{
	int		cmpt;

	cmpt = 0;
	if (n <= 0)
		cmpt++;
	while (n != 0)
	{
		cmpt++;
		n = n / 10;
	}
	return (cmpt);
}

char			*ft_itoa(int n)
{
	char	*new;
	int		i;
	int		res;

	res = ft_cmpt(n);
	i = res - 1;
	if (!(new = ft_strnew(res)))
		return (NULL);
	if (n == -2147483648)
		return (ft_strcpy(new, "-2147483648"));
	if (n < 0)
	{
		new[0] = '-';
		n = -n;
	}
	if (n == 0)
		new[0] = '0';
	while (n != 0)
	{
		new[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	new[res] = '\0';
	return (new);
}
