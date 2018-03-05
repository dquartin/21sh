/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:31:31 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:45:30 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_lstaddnew(t_hist **alst, t_hist *new)
{
	new->next = *alst;
	new->prev = NULL;
	if (*alst)
		(new->next)->prev = new;
	*alst = new;
}

t_hist	*ft_lstcreate(void const *content)
{
	t_hist	*new;

	CHECKMC(new = (t_hist*)malloc(sizeof(t_hist)));
	if (!content)
		new->histo = NULL;
	else
		new->histo = ft_strdup(content);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int		ft_lst_size(t_hist *begin_list)
{
	int i;

	if (begin_list == NULL)
		return (0);
	i = 0;
	while (begin_list)
	{
		begin_list = begin_list->next;
		i++;
	}
	return (i);
}

t_hist	*ft_lst_at(t_hist *begin_list, unsigned int nbr)
{
	unsigned int j;

	j = 0;
	while (begin_list != NULL && j != nbr)
	{
		begin_list = begin_list->next;
		j++;
	}
	if (j != nbr)
		return (NULL);
	return (begin_list);
}
