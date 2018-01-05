/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:33:39 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 16:06:27 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;

	i = 0;
	if (s2[0] == '\0')
		return ((char*)s1);
	while (s1[i])
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while ((s1[i + j] == s2[j]) && s2[j] && s1[i + j])
				j++;
			if (s2[j] == '\0')
				return ((char*)&(s1[i]));
		}
		i++;
	}
	return (NULL);
}
