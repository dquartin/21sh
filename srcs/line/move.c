/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 09:42:35 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:49:42 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_move_bis(t_index **index, t_hist **list,
		char *buff, struct winsize size)
{
	int		total;

	total = buff[0] + buff[1] + buff[2] + buff[3] + buff[4] + buff[5];
	if (total == HOME)
		home(index, size);
	else if (total == END)
		end(index, size);
	else if (total == UP_ARROW)
		history(index, list);
	else if (total == DOWN_ARROW)
		back_history(index, list);
	else if (total == SHIFT_RIGHT)
		shift_right(index);
	else if (total == SHIFT_LEFT)
		shift_left(index);
	else if (total == ALT_S)
		select_mode(index);
	else if (total == ALT_V)
		copy_n_paste(index);
	else if (total == SHIFT_UP && (*index)->x > size.ws_col)
		(*index)->i = shift_up((*index)->i, *index, size);
	else if (total == SHIFT_DOWN && (*index)->x > size.ws_col)
		shift_down(index);
	else
		other_case(index, buff, size);
}

void	ft_move_int(t_index **index, t_hist **list,
		char *buff, struct winsize size)
{
	int			total;
	t_hist		*beginlst;

	beginlst = *list;
	total = buff[0] + buff[1] + buff[2] + buff[3] + buff[4] + buff[5];
	if (total != UP_ARROW && total != DOWN_ARROW)
		*list = beginlst;
	if (total == DEL)
	{
		begin(index);
		if ((*index)->i > 0)
			ft_lst_clear(&((*index)->start));
	}
	else if (total == RIGHT_ARROW)
		go_to_right(index, size);
	else if (total == LEFT_ARROW)
		(*index)->i = go_to_left((*index)->i);
	else
		ft_move_bis(index, list, buff, size);
}

void	init(t_index **index, char ***environ)
{
	char	*tmp;

	(*index)->environ = ft_envcpy(*environ);
	tmp = ft_getenv(*environ, "PROMPT");
	(*index)->prompt = ft_atoi(tmp);
	(*index)->line = ft_strnew(20000);
	(*index)->list = NULL;
	(*index)->start = NULL;
	(*index)->x = 0;
	(*index)->i = (*index)->x;
	ft_strdel(&tmp);
}

char	*enter(t_index *index, t_hist **list,
		char ***environ, struct winsize size)
{
	char	*tmp;

	delete_lines(environ);
	free(*environ);
	*environ = ft_envcpy(index->environ);
	tmp = ft_strdup(index->line);
	if (*list && (*list)->histo)
	{
		while ((*list)->prev)
			*list = (*list)->prev;
	}
	if (index->i != index->x)
		end(&index, size);
	free_index(&index);
	return (tmp);
}

char	*ft_move(t_hist **list, char ***environ)
{
	char			buff[7];
	int				total;
	t_index			*index;
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	CHECKMC(index = (t_index*)malloc(sizeof(t_index)));
	init(&index, environ);
	while (1)
	{
		ft_bzero(buff, 6);
		read(0, buff, 6);
		total = buff[0] + buff[1] + buff[2] + buff[3] + buff[4] + buff[5];
		if (total == CTRL_D)
			ctrl_d(index, buff);
		if (total == ENTER || g_heredoc == 2)
			return (enter(index, list, environ, size));
		if (total == CTRL_C)
			return (ctrl_c_move(index, buff));
		else
			ft_move_int(&index, list, buff, size);
	}
	return (NULL);
}
