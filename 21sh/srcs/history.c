/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:00:48 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/17 11:07:01 by dquartin         ###   ########.fr       */
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

int		back_history(int i, int *x, char **line, t_hist **list)
{
	while ((*list) && (*list)->prev &&
	(ft_strcmp((*list)->prev->histo, (*list)->histo) == 0))
		*list = (*list)->prev;
	if (*list)
	{
		i = call_delchar(i, x, *line);
		ft_strdel(line);
		if ((*list)->prev)
		{
			*list = (*list)->prev;
			*line = ft_strdup((*list)->histo);
			ft_putstrin(*line);
			(*x) = ft_strlen(*line);
			i = (*x);
		}
		else
			*line = ft_strnew(10);
	}
	return (i);
}
