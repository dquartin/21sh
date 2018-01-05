/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 09:51:28 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/05 16:46:29 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		other_case(char **line, int i, int *x, char *buffer)
{
	*line = promptchar(buffer, *line, x);
	insertchar(i, line, buffer);
	i++;
	return (i);
}

int     shift_down(int i, int *x, int prompt, char **environ)
{
	int             k;
	struct winsize  size;

	ioctl(0, TIOCGWINSZ, &size);
	if (i < *x)
	{
		if (i + size.ws_col > *x)
			i = end(i, *x, size, environ);
		else if ((i + prompt) % size.ws_col != 0)
		{
			k = i;
			i = i + size.ws_col;
			while ((k + prompt) % size.ws_col != 0)
			{
				tputs(tgetstr("nd", NULL), 1, ft_putin);
				k++;
			}
			tputs(tgetstr("do", NULL), 1, ft_putin);
			while (k < i)
			{
				tputs(tgetstr("nd", NULL), 1, ft_putin);
				k++;
			}
		}
		else
		{
			tputs(tgetstr("do", NULL), 100, ft_putin);
			i = i + size.ws_col;
		}
	}
	return (i);
}

int     shift_up(int i, struct winsize size)
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
	return (i);
}
