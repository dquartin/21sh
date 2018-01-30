/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:15:35 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 16:49:52 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	if (!(new = ft_strnew(ft_strlen((char*)s1) + ft_strlen((char*)s2) + 1)))
		return (NULL);
	new = ft_strcat(new, s1);
	new = ft_strcat(new, s2);
	return (new);
}
