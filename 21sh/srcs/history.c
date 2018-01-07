/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:00:48 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/07 12:29:07 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_hist	*stock_history(char *line, t_hist *list)
{
	t_hist	*begin_list;

	begin_list = ft_lstcreate(line);
	ft_lstaddnew(&list, begin_list);
	return (list);
}

void	back_history(t_index **index, t_hist **list)
{
	while ((*list) && (*list)->prev &&
	(ft_strcmp((*list)->prev->histo, (*list)->histo) == 0))
		*list = (*list)->prev;
	if (*list)
	{
		call_delchar(index);
		ft_strdel(&(*index)->line);
		if ((*list)->prev)
		{
			*list = (*list)->prev;
			(*index)->line = ft_strdup((*list)->histo);
			ft_putstrin((*index)->line);
			(*index)->x = ft_strlen((*index)->line);
			(*index)->i = (*index)->x;
		}
		else
			(*index)->line = ft_strnew(10000);
	}
}

void	history(t_index **index, t_hist **list)
{
	while ((*list) && (*list)->next &&
			(ft_strcmp((*list)->next->histo, (*list)->histo) == 0))
		*list = (*list)->next;
	if (*list)
	{
		call_delchar(index);
		ft_strdel(&(*index)->line);
		(*index)->line = ft_strdup((*list)->histo);
		ft_putstrin((*index)->line);
		(*index)->x = ft_strlen((*index)->line);
		(*index)->i = (*index)->x;
		if ((*list)->next)
			*list = (*list)->next;
	}
}
