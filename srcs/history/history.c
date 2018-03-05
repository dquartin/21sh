/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 13:00:48 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:46:27 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

t_hist	*get_history(char **environ)
{
	int		fd;
	char	*tmp;
	char	*line;
	t_hist	*list;

	line = NULL;
	list = NULL;
	tmp = ft_getenv(environ, "HIST_PATH");
	fd = open(tmp, O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		list = stock_history(line, list);
		if (line)
			ft_strdel(&line);
	}
	close(fd);
	if (tmp)
		ft_strdel(&tmp);
	return (list);
}

void	save_history(t_hist *list, char **environ)
{
	char	*tmp;
	int		fd;

	tmp = ft_getenv(environ, "HIST_PATH");
	fd = open(tmp, O_WRONLY | O_TRUNC);
	while (list && list->next)
		list = list->next;
	while (list)
	{
		if (list->histo)
			ft_putendl_fd(list->histo, fd);
		list = list->prev;
	}
	close(fd);
	if (tmp)
		ft_strdel(&tmp);
}

void	create_history(char ***environ)
{
	int		fd;
	char	*tmp;

	if ((tmp = ft_getenv(*environ, "HOME")) == NULL)
		tmp = ft_strdup("/tmp");
	tmp = ft_strjoindel(tmp, "/.history");
	ft_setenv("HIST_PATH", tmp, environ);
	fd = open(tmp, APPEND);
	close(fd);
	if (tmp)
		ft_strdel(&tmp);
}

t_hist	*stock_history(char *line, t_hist *list)
{
	t_hist	*begin_list;

	begin_list = ft_lstcreate(line);
	ft_lstaddnew(&list, begin_list);
	return (list);
}

void	back_history(t_index **index, t_hist **list)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	while ((*list) && (*list)->prev && (*list)->histo && (*list)->prev->histo &&
			((ft_strcmp((*list)->prev->histo, (*list)->histo) == 0)
			|| ft_strcmp((*list)->prev->histo, (*index)->line) == 0))
		*list = (*list)->prev;
	if (*list && (*list)->histo)
	{
		end(index, size);
		call_delchar(index);
		GO(CLR);
		ft_strdel(&(*index)->line);
		if ((*list)->prev)
		{
			*list = (*list)->prev;
			(*index)->line = ft_strnew(10000);
			(*index)->line = ft_strcpy((*index)->line, (*list)->histo);
			ft_putstrin((*index)->line);
			(*index)->x = ft_strlen((*index)->line);
			(*index)->i = (*index)->x;
		}
		else
			(*index)->line = ft_strnew(10000);
	}
}
