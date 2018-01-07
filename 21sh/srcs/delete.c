/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 08:59:49 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/07 12:25:55 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	delete_lines(char **stock)
{
	int		i;

	i = 0;
	while (stock[i])
	{
		ft_strdel(stock + i);
		i++;
	}
	free(stock);
	stock = NULL;
}

void	delinline(t_index **index)
{
	while ((*index)->line[(*index)->i])
	{
		(*index)->line[(*index)->i - 1] = (*index)->line[(*index)->i];
		(*index)->i++;
	}
	(*index)->line[(*index)->i - 1] = '\0';
}

void	delchar(t_index **index)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	tputs(tgetstr("le", NULL), 0, ft_putin);
	tputs(tgetstr("dc", NULL), 0, ft_putin);
	delinline(index);
	if (((*index)->i + 1 + (*index)->prompt) % size.ws_col == 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_putin);
		tputs(tgetstr("dc", NULL), 0, ft_putin);
		tputs(tgetstr("dc", NULL), 0, ft_putin);
		ft_putchar((*index)->line[(*index)->i - 1]);
		tputs(tgetstr("nd", NULL), 0, ft_putin);
	}
}

void	call_delchar(t_index **index)
{
	while ((*index)->x > 0)
	{
		tputs(tgetstr("le", NULL), 1, ft_putin);
		tputs(tgetstr("dc", NULL), 1, ft_putin);
		delinline(index);
		(*index)->x--;
		(*index)->i--;
	}
}

void	begin(t_index **index)
{
	if ((*index)->i > 0)
	{
		delchar(index);
		(*index)->x--;
		(*index)->i--;
	}
}
