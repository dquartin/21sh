/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 16:26:48 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:46:47 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	history(t_index **index, t_hist **list)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	while ((*list) && (*list)->next && (*list)->histo && (*list)->next->histo &&
			((ft_strcmp((*list)->next->histo, (*list)->histo) == 0)
			|| ft_strcmp((*list)->histo, (*index)->line) == 0))
		*list = (*list)->next;
	if (*list && (*list)->histo)
	{
		end(index, size);
		call_delchar(index);
		GO(CLR);
		ft_strdel(&(*index)->line);
		(*index)->line = ft_strnew(10000);
		(*index)->line = ft_strcpy((*index)->line, (*list)->histo);
		ft_putstrin((*index)->line);
		(*index)->x = ft_strlen((*index)->line);
		(*index)->i = (*index)->x;
		if ((*list)->next)
			*list = (*list)->next;
	}
}
