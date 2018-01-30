/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 09:25:59 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:23:48 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

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
	char			*tmp;

	nb = 1;
	tmp = ft_getenv((*index)->environ, "PROMPT");
	(*index)->prompt = ft_atoi(tmp);
	ft_strdel(&tmp);
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
