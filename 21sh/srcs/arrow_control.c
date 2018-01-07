/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 09:25:59 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/07 12:32:21 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	shift_right_bis(t_index **index, struct winsize size)
{
	while ((*index)->line[(*index)->i + 1] > 32 &&
	((*index)->i + (*index)->prompt) % size.ws_col != 0)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putin);
		(*index)->i++;
	}
	if (((*index)->i + (*index)->prompt) % size.ws_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_putin);
		while ((*index)->line[(*index)->i + 1] > 32 &&
		(*index)->i != (*index)->x)
		{
			tputs(tgetstr("nd", NULL), 1, ft_putin);
			(*index)->i++;
		}
	}
	tputs(tgetstr("nd", NULL), 1, ft_putin);
	(*index)->i++;
}

void	shift_right(t_index **index)
{
	struct winsize	size;
	int				nb;

	nb = 1;
	(*index)->prompt = ft_atoi(ft_getenv((*index)->environ, "PROMPT"));
	ioctl(0, TIOCGWINSZ, &size);
	if ((*index)->i < (*index)->x)
	{
		if ((*index)->x + (*index)->prompt > size.ws_col)
			shift_right_bis(index, size);
		else
		{
			while ((*index)->line[(*index)->i + 1] > 32 &&
			((*index)->i + (*index)->prompt) % size.ws_col != 0)
			{
				tputs(tgetstr("nd", NULL), 1, ft_putin);
				(*index)->i++;
			}
			tputs(tgetstr("nd", NULL), 1, ft_putin);
			(*index)->i++;
		}
	}
}

void	shift_left(t_index **index)
{
	if ((*index)->i > 0)
	{
		while ((*index)->line[(*index)->i - 1] > 32)
		{
			tputs(tgetstr("le", NULL), 1, ft_putin);
			(*index)->i--;
		}
		if ((*index)->i != 0)
		{
			tputs(tgetstr("le", NULL), 1, ft_putin);
			(*index)->i--;
		}
	}
}
