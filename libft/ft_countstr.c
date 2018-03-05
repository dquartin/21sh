/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 11:15:41 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:34:14 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countstr(char *s1, char *s2)
{
	int		count;

	count = 0;
	while (s1)
	{
		if (ft_strstr(s1, s2))
		{
			count++;
			s1 = ft_strstr(s1, s2) + 2;
		}
		else
			return (count);
	}
	return (count);
}
