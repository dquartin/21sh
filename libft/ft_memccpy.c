/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:40:05 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 21:59:31 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*dest_tmp;
	const char	*src_tmp;
	size_t		i;

	dest_tmp = dest;
	src_tmp = src;
	i = 0;
	while (i < n)
	{
		dest_tmp[i] = src_tmp[i];
		if (src_tmp[i] == c)
			return ((void*)dest + i + 1);
		i++;
	}
	return (0);
}
