/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 20:36:26 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 19:38:42 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_tmp;
	const unsigned char	*s2_tmp;
	size_t				i;

	s1_tmp = s1;
	s2_tmp = s2;
	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && s1_tmp[i] == s2_tmp[i])
		i++;
	return (s1_tmp[i] - s2_tmp[i]);
}
