/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnrstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 15:53:57 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/30 15:58:27 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnrstr(const char *s1, const char *s2, int size)
{
	int			i;
	int			j;

	i = size;
	if (s2[0] == '\0')
		return ((char*)s1);
	while (i > 0)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (i + j < size && s2[j] && s1[i + j] && s1[i + j] == s2[j])
				j++;
			if (s2[j] == '\0')
				return ((char*)&(s1[i]));
		}
		i--;
	}
	return (NULL);
}
