/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:15:02 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 19:28:43 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive_del(t_list *lst, void (*del)(void *, size_t))
{
	if (lst->next != NULL)
		ft_recursive_del(lst->next, (*del));
	del(lst->content, lst->content_size);
	free(lst);
}

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	ft_recursive_del(*alst, (*del));
	*alst = NULL;
}
