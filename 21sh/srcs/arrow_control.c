/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 09:25:59 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/05 16:25:02 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		shift_right(int i, int x, int prompt, char *line)
{
	struct winsize  size;
	int             nb;

	nb = 1;
	ioctl(0, TIOCGWINSZ, &size);
	if (i < x)
	{
		if (x + prompt > size.ws_col)
		{
			while (line[i + 1] > 32 && (i + prompt) % size.ws_col != 0)
			{
				tputs(tgetstr("nd", NULL), 1, ft_putin);
				i++;
			}
			if ((i + prompt) % size.ws_col == 0)
			{
				tputs(tgetstr("do", NULL), 1, ft_putin);
				while (line[i + 1] > 32 && i != x)
				{
					tputs(tgetstr("nd", NULL), 1, ft_putin);
					i++;
				}
			}
			tputs(tgetstr("nd", NULL), 1, ft_putin);
			i++;
		}
		else
		{
			while (line[i + 1] > 32 && (i + prompt) % size.ws_col != 0)
			{
				tputs(tgetstr("nd", NULL), 1, ft_putin);
				i++;
			}
			tputs(tgetstr("nd", NULL), 1, ft_putin);
			i++;
		}
	}
	return (i);
}

int		shift_left(int i, char *line)
{
	if (i > 0)
	{
		while (line[i - 1] > 32)
		{
			tputs(tgetstr("le", NULL), 100, ft_putin);
			i--;
		}
		if (i != 0)
		{
			tputs(tgetstr("le", NULL), 100, ft_putin);
			i--;
		}
	}
	return (i);
}

int		history(int i, int *x, char **line, t_hist **list)
{
	while ((*list) && (*list)->next &&
			(ft_strcmp((*list)->next->histo, (*list)->histo) == 0))
		*list = (*list)->next;
	if (*list)
	{
		i = call_delchar(i, x, *line);
		ft_strdel(line);
		*line = ft_strdup((*list)->histo);
		ft_putstrin(*line);
		(*x) = ft_strlen(*line);
		i = (*x);
		if ((*list)->next)
			*list = (*list)->next;
	}
	return (i);
}

int		call_delchar(int i, int *x, char *line)
{
	while ((*x) > 0)
	{

		tputs(tgetstr("le", NULL), 1, ft_putin);
		tputs(tgetstr("dc", NULL), 1, ft_putin);
		delinline(i - 1, &line);
		(*x)--;
		i--;
	}
	return (i);
}

int		begin(int i, int *x, int prompt, char *line)
{
	if (i > 0)
	{
		delchar(i - 1, prompt, line);
		(*x)--;
		i--;
	}
	return (i);
}
