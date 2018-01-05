/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 09:42:35 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/05 16:36:55 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    insertchar(int i, char **line, char *buffer)
{
	char            *tmp;
	int             j;
	int             x;
	int             k;

	j = 0;
	x = ft_strlen(*line);
	tmp = ft_strsub((*line), i, ft_strlen(*line));
	(*line)[i] = buffer[0];
	i++;
	k = i;
	//tputs(tgetstr("ei", NULL), 1, ft_putin);
	ft_putstrin(tmp);
	//tputs(tgetstr("im", NULL), 1, ft_putin);
	i = ft_strlen(*line);
	while (i != k)
	{
		tputs(tgetstr("le", NULL), 1, ft_putin);
		i--;
	}
	while ((*line)[i])
	{
		(*line)[i] = tmp[j];
		i++;
		j++;
	}
	ft_strdel(&tmp);
}

void	delinline(int i, char **line)
{
	while ((*line)[i + 1])
	{
		(*line)[i] = (*line)[i + 1];
		i++;
	}
	(*line)[i] = '\0';
}

void	delchar(int i, int prompt, char *line)
{
	struct winsize  size;

	ioctl(0, TIOCGWINSZ, &size);
	tputs(tgetstr("le", NULL), 0, ft_putin);
	tputs(tgetstr("dc", NULL), 0, ft_putin);
	delinline(i, &line);
	i++;
	if ((i + prompt) % size.ws_col == 0)
	{
		tputs(tgetstr("le", NULL), 0, ft_putin);
		tputs(tgetstr("dc", NULL), 0, ft_putin);
		tputs(tgetstr("dc", NULL), 0, ft_putin);
		ft_putchar(line[i - 2]);
		tputs(tgetstr("nd", NULL), 0, ft_putin);
	}
}

char	*promptchar(char *buffer, char *line, int *x)
{
	if (*x % 10000 == 0)
		line = ft_realloc(line, (int)ft_strlen(line), (int)(ft_strlen(line) + 10000));
	write(0, &buffer[0], 1);
	(*x)++;
	return (line);
}

char	*ft_move(t_hist **list, char ***environ)
{
	char	*line;
	char	buff[7];
	int		i;
	int		x;
	int		prompt;
	int		total;
	t_hist	*beginlst;
	struct winsize  size;

	ioctl(0, TIOCGWINSZ, &size);
	prompt = ft_atoi(ft_getenv(*environ, "PROMPT"));
	line = ft_strnew(2000);
	beginlst = *list;
	x = 0;
	i = x;
	while (1)
	{
		ft_bzero(buff, 6);
		read(0, buff, 6);
		total = buff[0] + buff[1] + buff[2] + buff[3] + buff[4] + buff[5];
		if (total != UP_ARROW && total != DOWN_ARROW)
			*list = beginlst;
		if (total == DEL)
			i = begin(i, &x, prompt, line);
		else if (total == ENTER)
		{
			ft_bzero(buff, 7);
			if (i != x)
				i = end(i, x, size, *environ);
			return (line);
		}
		else if (total == RIGHT_ARROW)
			i = go_to_right(i, x, prompt, size);
		else if (total == LEFT_ARROW)
			i = go_to_left(i);
		else if (total == HOME)
			i = home(i, x, size, *environ);
		else if (total == END)
			i = end(i, x, size, *environ);
		else if (total == UP_ARROW)
			i = history(i, &x, &line, list);
		else if (total == DOWN_ARROW)
			i = back_history(i, &x, &line, list);
		else if (total == SHIFT_RIGHT)
			i = shift_right(i, x, prompt, line);
		else if (total == SHIFT_LEFT)
			i = shift_left(i, line);
		else if (total == ALT_S)
			select_mode(line, &i, &x, environ);
		else if (total == ALT_V)
			copy_n_paste(&line, &i, &x, environ);
		else if (total == SHIFT_UP && x > size.ws_col)
			i = shift_up(i, size);
		else if (total == SHIFT_DOWN && x > size.ws_col)
			i = shift_down(i, &x, prompt, *environ);
		else
			i = other_case(&line, i, &x, buff);
	}
	return (NULL);
}
