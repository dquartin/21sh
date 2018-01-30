/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 20:04:19 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 19:41:14 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char		*str_tmp;
	size_t			i;

	str_tmp = str;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)str_tmp[i] == (unsigned char)c)
			return ((char *)&(str_tmp[i]));
		i++;
	}
	return (NULL);
}
