/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 09:23:38 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/05 16:31:47 by dquartin         ###   ########.fr       */
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

void	quit_mode(char *stock, int *i, int *x, char *line, char **environ)
{
	struct winsize size;

	ioctl(0, TIOCGWINSZ, &size);
	tputs(tgetstr("ei", NULL), 100, ft_putin);
	ft_strdel(&stock);
	*i = home(*i, *x, size, environ);
	*x = (int)ft_strlen(line);
	ft_putstrin(line);
	*i = *x;
	tputs(tgetstr("im", NULL), 100, ft_putin);
}

void	select_right(int *i, int *x, int prompt, char *stock, char *line)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	if (*i < *x)
	{
		*i = go_to_right(*i, *x, prompt, size);
		copy_char(line, i, &stock);
	}
}

void	select_left(int *i, char *stock, char *line)
{
	if (*i > 0)
	{
		copy_char(line, i, &stock);
		*i = go_to_left(*i);
	}
}

void	select_mode(char *line, int *i, int *x, char ***environ)
{
	char	buff[6];
	char	*stock;
	int		total;
	int		prompt;

	stock = NULL;
	prompt = ft_atoi(ft_getenv(*environ, "PROMPT"));
	stock = create_stock(line);
	while (1)
	{
		ft_bzero(buff, 6);
		read(0, buff, 6);
		total = buff[0] + buff[1] + buff[2] + buff[3] + buff[4] + buff[5];
		if (total == ALT_S)
		{
			quit_mode(stock, i, x, line, *environ);
			return ;
		}
		else if (total == RIGHT_ARROW)
			select_right(i, x, prompt, stock, line);
		else if (total == LEFT_ARROW)
			select_left(i, stock, line);
		if (total == ALT_C)
			copy_select(stock, x, environ);
	}
}
