/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:47:24 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 21:45:22 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_end;

	i = 0;
	if (size == 0)
		return (ft_strlen(dest));
	while (dest[i] && i < size)
		i++;
	dest_end = i;
	while (src[i - dest_end] && i < size - 1)
	{
		dest[i] = src[i - dest_end];
		i++;
	}
	while (i < size)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest_end + ft_strlen(src));
}
