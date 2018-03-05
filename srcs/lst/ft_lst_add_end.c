/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_add_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 12:04:58 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 16:00:44 by dquartin         ###   ########.fr       */
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

void	ft_hst_clear(t_hist **begin_list)
{
	t_hist	*destroy;

	while (*begin_list != NULL)
	{
		destroy = *begin_list;
		*begin_list = (*begin_list)->next;
		ft_strdel(&(destroy->histo));
		free(destroy);
		destroy = NULL;
	}
}
