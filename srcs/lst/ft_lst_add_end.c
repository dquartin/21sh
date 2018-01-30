/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 12:04:58 by hlely             #+#    #+#             */
/*   Updated: 2018/01/29 16:49:50 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_lst_add_end(t_list **alst, t_list *new)
{
	t_list *begin;

	if (*alst == NULL)
		*alst = new;
	else
	{
		begin = *alst;
		while ((*alst)->next)
			*alst = (*alst)->next;
		(*alst)->next = new;
		*alst = begin;
	}
}

void	ft_lst_clear(t_list **begin_list)
{
	t_list	*destroy;

	while (*begin_list != NULL)
	{
		destroy = *begin_list;
		*begin_list = (*begin_list)->next;
		free(destroy->content);
		destroy->content = NULL;
		free(destroy);
		destroy = NULL;
	}
}
