/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:32:36 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 16:35:40 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*tab;
	size_t	i;

	i = 0;
	if (!(tab = (char*)malloc(size + 1)))
		return (NULL);
	while (i <= size)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}
