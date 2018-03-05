/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 09:25:59 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:34:39 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	shift_right_bis(t_index **index, struct winsize size)
{
	while (((CHECKNEXT && CHECKCHAR) ||
	((*index)->line[(*index)->i] <= 32)) &&
	(CHECKSIZE((*index)->i) != 0 && (*index)->i != (*index)->x))
		go_to_right(index, size);
	if (CHECKSIZE((*index)->i) == 0)
	{
		GO(RIGHT);
		(*index)->i++;
		while (((CHECKNEXT && CHECKCHAR) ||
		((*index)->line[(*index)->i] <= 32)) &&
		(CHECKSIZE((*index)->i) != 0 && (*index)->i != (*index)->x))
			go_to_right(index, size);
	}
	go_to_right(index, size);
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
			while (((CHECKNEXT && CHECKCHAR) ||
			((*index)->line[(*index)->i] <= 32)) &&
			(CHECKSIZE((*index)->i) != 0 && (*index)->i != (*index)->x))
				go_to_right(index, size);
			go_to_right(index, size);
		}
	}
}

void	shift_left(t_index **index)
{
	if ((*index)->i > 0)
	{
		while ((*index)->i > 0 &&
		(((*index)->line[(*index)->i - 1] > 32
		&& CHECKCHAR) ||
		(*index)->line[(*index)->i] <= 32))
		{
			GO(LEFT);
			(*index)->i--;
		}
		if ((*index)->i != 0)
		{
			GO(LEFT);
			(*index)->i--;
		}
	}
}
