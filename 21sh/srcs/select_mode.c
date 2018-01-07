/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 09:23:38 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/07 11:37:00 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*create_stock(char *line)
{
	char	*stock;
	int		j;

	j = 0;
	stock = ft_strdup(line);
	while (stock[j])
	{
		stock[j] = '\0';
		j++;
	}
	return (stock);
}

void	quit_mode(char *stock, t_index **index)
{
	struct winsize size;

	ioctl(0, TIOCGWINSZ, &size);
	tputs(tgetstr("ei", NULL), 1, ft_putin);
	ft_strdel(&stock);
	home(index, size);
	(*index)->x = (int)ft_strlen((*index)->line);
	ft_putstrin((*index)->line);
	(*index)->i = (*index)->x;
	tputs(tgetstr("im", NULL), 1, ft_putin);
}

void	select_right(char *stock, t_index **index)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	(*index)->prompt = ft_atoi(ft_getenv((*index)->environ, "PROMPT"));
	if ((*index)->i < (*index)->x)
	{
		go_to_right(index, size);
		copy_char(index, &stock);
	}
}

void	select_left(char *stock, t_index **index)
{
	if ((*index)->i > 0)
	{
		copy_char(index, &stock);
		(*index)->i = go_to_left((*index)->i);
	}
}

void	select_mode(t_index **index)
{
	char	buff[6];
	char	*stock;
	int		total;

	stock = NULL;
	(*index)->prompt = ft_atoi(ft_getenv((*index)->environ, "PROMPT"));
	stock = create_stock((*index)->line);
	while (1)
	{
		ft_bzero(buff, 6);
		read(0, buff, 6);
		total = buff[0] + buff[1] + buff[2] + buff[3] + buff[4] + buff[5];
		if (total == ALT_S)
		{
			quit_mode(stock, index);
			return ;
		}
		else if (total == RIGHT_ARROW)
			select_right(stock, index);
		else if (total == LEFT_ARROW)
			select_left(stock, index);
		if (total == ALT_C)
			copy_select(stock, index);
	}
}
