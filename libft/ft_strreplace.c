/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:44:55 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/31 14:45:21 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *src, char *new, int size)
{
	char	*tmp;

	tmp = ft_strsub(src, size, ft_strlen(src));
	ft_strdel(&src);
	src = ft_strjoin(new, tmp);
	ft_strdel(&tmp);
	return (src);
}
