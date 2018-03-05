/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 09:51:28 by dquartin          #+#    #+#             */
/*   Updated: 2018/03/01 13:57:01 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	other_case(t_index **index, char *buffer, struct winsize size)
{
	if (buffer[0] != 9 && ft_isprint(buffer[0]))
	{
		(*index)->line = promptchar(buffer, index);
		insertchar(index, buffer);
		if (CHECKSIZE((*index)->i) == -1)
			GO(DOWN);
		(*index)->i++;
		ft_lst_clear(&((*index)->start));
	}
}

void	shift_down_bis(t_index **index, struct winsize size)
{
	int				k;

	k = (*index)->i;
	(*index)->i = (*index)->i + size.ws_col;
	while (CHECKSIZE(k) != 0)
	{
		GO(RIGHT);
		k++;
	}
	GO(DOWN);
	while (k < (*index)->i)
	{
		GO(RIGHT);
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
		else if (CHECKSIZE((*index)->i) != 0)
			shift_down_bis(index, size);
		else
		{
			GO(DOWN);
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
			GO(UP);
			i = i - size.ws_col;
			while (i < 0)
			{
				GO(RIGHT);
				i++;
			}
		}
		else if (i > 0)
		{
			GO(UP);
			i = i - size.ws_col;
		}
	}
	return (i);
}
