/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:25:43 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/08 13:33:19 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == c)
			j = i;
		i++;
	}
	if (str[i] == '\0' && c == 0)
		return ((char*)&(str[i]));
	if (j == -1)
		return (0);
	else
		return ((char*)&(str[j]));
}
