/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 19:46:22 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 13:52:58 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_tmp;
	char		temp[n];
	const char	*src_tmp;
	size_t		i;

	dest_tmp = dest;
	src_tmp = src;
	i = 0;
	if (n > 100000000)
		return (0);
	while (i < n)
	{
		temp[i] = src_tmp[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		dest_tmp[i] = temp[i];
		i++;
	}
	return (dest);
}
