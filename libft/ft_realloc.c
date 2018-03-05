/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 19:33:06 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/09 09:48:03 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, int old_size, int new_size)
{
	void	*new;

	if (old_size > new_size && ptr)
		return (NULL);
	new = (void *)ft_memalloc(new_size);
	if (!new)
		return (NULL);
	ft_memset(new, 0, new_size);
	if (ptr == NULL)
		return (new);
	new = ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}
