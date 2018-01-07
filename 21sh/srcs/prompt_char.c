/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 12:26:05 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/07 12:36:56 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*promptchar(char *buffer, t_index **index)
{
	if ((*index)->x % 10000 == 0)
		(*index)->line = ft_realloc((*index)->line,
				(int)ft_strlen((*index)->line),
				(int)(ft_strlen((*index)->line) + 10000));
	write(0, &buffer[0], 1);
	(*index)->x++;
	return ((*index)->line);
}

void	insertchar(t_index **index, char *buffer)
{
	struct winsize	size;
	int				j;

	ioctl(0, TIOCGWINSZ, &size);
	(*index)->prompt = ft_atoi(ft_getenv((*index)->environ, "PROMPT"));
	j = 0;
	while ((*index)->x > (*index)->i)
	{
		(*index)->line[(*index)->x] = (*index)->line[(*index)->x - 1];
		(*index)->x--;
	}
	(*index)->line[(*index)->i] = buffer[0];
	(*index)->x = ft_strlen((*index)->line);
	(*index)->i++;
	if ((*index)->i < (*index)->x)
	{
		if (((*index)->i + (*index)->prompt) % size.ws_col == 0)
			tputs(tgetstr("do", NULL), 1, ft_putin);
		tputs(tgetstr("sc", NULL), 1, ft_putin);
		tputs(tgetstr("ei", NULL), 1, ft_putin);
		ft_putstrin((*index)->line + (*index)->i);
		tputs(tgetstr("im", NULL), 1, ft_putin);
		tputs(tgetstr("rc", NULL), 1, ft_putin);
	}
	(*index)->i--;
}
