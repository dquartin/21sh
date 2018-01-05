/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 16:49:58 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/02 13:53:16 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		go_to_right(int i, int x)
{
	if (i < x)
	{
		tputs(tgetstr("nd", NULL), 100, ft_putin);
		i++;
	}
	return (i);
}

int		go_to_left(int i)
{
	if (i > 0)
	{
		tputs(tgetstr("le", NULL), 100, ft_putin);
		i--;
	}
	return (i);
}

int		home(int i, int x, struct winsize size, char **environ)
{
	int		prompt;

	prompt = ft_atoi(ft_getenv(environ, "PROMPT"));
	if (x > size.ws_col)
	{
		while (i > prompt)
		{
			tputs(tgetstr("le", NULL), 100, ft_putin);
			i--;
		}
	}
	while (i > 0)
	{
		tputs(tgetstr("le", NULL), 100, ft_putin);
		i--;
	}
	return (i);
}

int		end(int i, int x, struct winsize size, char **environ)
{
	int		prompt;
	int		line;

	line = 0;
	i = home(i, x, size, environ);
	prompt = ft_atoi(ft_getenv(environ, "PROMPT"));
	if (x > size.ws_col)
	{
		line = x / size.ws_col + 1;
		if (i >= x)
			return (i);
		while (x - i > size.ws_col)
		{
			tputs(tgetstr("do", NULL), 100, ft_putin);
			i = size.ws_col + i;
		}
		while (i < x + prompt)
		{
			tputs(tgetstr("nd", NULL), 100, ft_putin);
			i++;
		}
		i = x;
	}
	else
	{
		while (i < x)
		{
			tputs(tgetstr("nd", NULL), 100, ft_putin);
			i++;
		}
	}
	return (i);
}