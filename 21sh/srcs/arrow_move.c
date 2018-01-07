/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 16:49:58 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/07 12:07:29 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	go_to_right(t_index **index, struct winsize size)
{
	if ((*index)->i < (*index)->x)
	{
		if (((*index)->i + (*index)->prompt + 1) % size.ws_col == 0)
			tputs(tgetstr("do", NULL), 1, ft_putin);
		else
			tputs(tgetstr("nd", NULL), 1, ft_putin);
		(*index)->i++;
	}
}

int		go_to_left(int i)
{
	if (i > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_putin);
		i--;
	}
	return (i);
}

void	home(t_index **index, struct winsize size)
{
	(*index)->prompt = ft_atoi(ft_getenv((*index)->environ, "PROMPT"));
	if ((*index)->x > size.ws_col)
	{
		while ((*index)->i > (*index)->prompt)
		{
			tputs(tgetstr("le", NULL), 1, ft_putin);
			(*index)->i--;
		}
	}
	while ((*index)->i > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_putin);
		(*index)->i--;
	}
}

void	end_bis(t_index **index, struct winsize size)
{
	if ((*index)->i >= (*index)->x)
		return ;
	while ((*index)->x - (*index)->i > size.ws_col)
	{
		tputs(tgetstr("do", NULL), 1, ft_putin);
		(*index)->i = size.ws_col + (*index)->i;
	}
	if (((*index)->x + (*index)->prompt) % size.ws_col < (*index)->prompt)
	{
		tputs(tgetstr("do", NULL), 1, ft_putin);
		(*index)->i = (*index)->i + size.ws_col;
	}
	while ((*index)->i < (*index)->x + (*index)->prompt)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putin);
		(*index)->i++;
	}
	(*index)->i = (*index)->x;
}

void	end(t_index **index, struct winsize size)
{
	home(index, size);
	if ((*index)->x > size.ws_col)
		end_bis(index, size);
	else
	{
		while ((*index)->i < (*index)->x)
		{
			tputs(tgetstr("nd", NULL), 1, ft_putin);
			(*index)->i++;
		}
		(*index)->i = (*index)->x;
	}
}
