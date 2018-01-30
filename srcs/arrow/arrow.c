/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 09:51:28 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 17:10:20 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	other_case(t_index **index, char *buffer, struct winsize size)
{
	if (buffer[0] != 9 && ft_isprint(buffer[0]))
	{
		(*index)->line = promptchar(buffer, index);
		insertchar(index, buffer);
		if ((*index)->i + (*index)->prompt % size.ws_col == 0)
			tputs(tgetstr("do", NULL), 1, ft_putin);
		(*index)->i++;
		ft_lst_clear(&((*index)->start));
		completion(index);
	}
}

void	shift_down_bis(t_index **index, struct winsize size)
{
	int				k;

	k = (*index)->i;
	(*index)->i = (*index)->i + size.ws_col;
	while ((k + (*index)->prompt) % size.ws_col != 0)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putin);
		k++;
	}
	tputs(tgetstr("do", NULL), 1, ft_putin);
	while (k < (*index)->i)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putin);
		k++;
	}
}

void	shift_down(t_index **index)
{
	struct winsize	size;
	char			*tmp;

	ioctl(0, TIOCGWINSZ, &size);
	tmp = ft_getenv((*index)->environ, "PROMPT");
	(*index)->prompt = ft_atoi(tmp);
	ft_strdel(&tmp);
	if ((*index)->i < (*index)->x)
	{
		if ((*index)->i + size.ws_col > (*index)->x)
			end(index, size);
		else if (((*index)->i + (*index)->prompt) % size.ws_col != 0)
			shift_down_bis(index, size);
		else
		{
			tputs(tgetstr("do", NULL), 1, ft_putin);
			(*index)->i = (*index)->i + size.ws_col;
		}
	}
}

int		shift_up(int i, t_index *index, struct winsize size)
{
	if (i + index->prompt > size.ws_col)
	{
		if (i - size.ws_col <= 0)
		{
			tputs(tgetstr("up", NULL), 100, ft_putin);
			i = i - size.ws_col;
			while (i < 0)
			{
				tputs(tgetstr("nd", NULL), 100, ft_putin);
				i++;
			}
		}
		else if (i > 0)
		{
			tputs(tgetstr("up", NULL), 100, ft_putin);
			i = i - size.ws_col;
		}
	}
	return (i);
}
