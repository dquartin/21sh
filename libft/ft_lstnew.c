/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 19:53:00 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/14 14:08:24 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
		new->content = NULL;
	else
	{
		if (!(new->content = (void *)malloc(sizeof(*content) * content_size)))
			return (NULL);
		new->content = ft_memcpy(new->content, content, content_size);
	}
	if (new->content == NULL)
		new->content_size = 0;
	else
		new->content_size = content_size;
	new->next = NULL;
	return (new);
}
