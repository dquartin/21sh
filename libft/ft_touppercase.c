/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_touppercase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:23:53 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/08 11:46:21 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_touppercase(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}