/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 16:49:58 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:20:51 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	go_to_right(t_index **index, struct winsize size)
{
	if ((*index)->i < (*index)->x)
	{
		if (((*index)->i + (*index)->prompt + 1) % size.ws_col == 0)
			GO(DOWN);
		else
			GO(RIGHT);
		(*index)->i++;
	}
}

int		go_to_left(int i)
{
	if (i > 0)
	{
		GO(LEFT);
		i--;
	}
	return (i);
}

void	home(t_index **index, struct winsize size)
{
	char	*tmp;

	tmp = ft_getenv((*index)->environ, "PROMPT");
	(*index)->prompt = ft_atoi(tmp);
	ft_strdel(&tmp);
	if ((*index)->x > size.ws_col)
	{
		while ((*index)->i > (*index)->prompt)
		{
			GO(LEFT);
			(*index)->i--;
		}
	}
	while ((*index)->i > 0)
	{
		GO(LEFT);
		(*index)->i--;
	}
}

void	end_bis(t_index **index, struct winsize size)
{
	if ((*index)->i >= (*index)->x)
		return ;
	while ((*index)->x - (*index)->i > size.ws_col)
	{
		GO(DOWN);
		(*index)->i = size.ws_col + (*index)->i;
	}
	if (CHECKSIZE((*index)->x) <= (*index)->prompt)
	{
		GO(DOWN);
		(*index)->i = (*index)->i + size.ws_col;
	}
	while ((*index)->i < (*index)->x + (*index)->prompt)
	{
		GO(RIGHT);
		(*index)->i++;
	}
	(*index)->i = (*index)->x;
}

void	end(t_index **index, struct winsize size)
{
	home(index, size);
	if ((*index)->x + (*index)->prompt > size.ws_col)
		end_bis(index, size);
	else
	{
		while ((*index)->i < (*index)->x)
		{
			GO(RIGHT);
			(*index)->i++;
		}
		(*index)->i = (*index)->x;
	}
}
