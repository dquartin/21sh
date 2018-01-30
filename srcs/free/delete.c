/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 08:59:49 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:39:08 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	delete_lines(char ***stock)
{
	int		i;

	i = 0;
	while ((*stock)[i])
	{
		ft_strdel((*stock) + i);
		i++;
	}
}

void	delinline(t_index **index)
{
	int		j;

	j = (*index)->i;
	while ((*index)->line[j])
	{
		(*index)->line[j - 1] = (*index)->line[j];
		j++;
	}
	(*index)->line[j - 1] = '\0';
}

void	delchar(t_index **index)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	if ((*index)->i > 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_putin);
		tputs(tgetstr("dc", NULL), 0, ft_putin);
		delinline(index);
		if (((*index)->i + (*index)->prompt) % size.ws_col == 0)
		{
			tputs(tgetstr("le", NULL), 0, ft_putin);
			tputs(tgetstr("dc", NULL), 0, ft_putin);
			tputs(tgetstr("dc", NULL), 0, ft_putin);
			ft_putchar((*index)->line[(*index)->i - 2]);
			tputs(tgetstr("nd", NULL), 0, ft_putin);
		}
		tputs(tgetstr("cd", NULL), 0, ft_putin);
		tputs(tgetstr("sc", NULL), 0, ft_putin);
		tputs(tgetstr("ei", NULL), 0, ft_putin);
		ft_putstrin((*index)->line + (*index)->i - 1);
		tputs(tgetstr("im", NULL), 0, ft_putin);
		tputs(tgetstr("rc", NULL), 0, ft_putin);
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
