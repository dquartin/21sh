/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 10:32:24 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:44:30 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static void	create_heredoc(char *line)
{
	int		fd;

	if (access("/tmp/.heredoc", F_OK) == 0)
		fd = open("/tmp/.heredoc", O_WRONLY | O_TRUNC);
	else
		fd = open("/tmp/.heredoc", O_CREAT | O_WRONLY, 0644);
	write(fd, line, ft_strlen(line));
	close(fd);
	fd = open("/tmp/.heredoc", O_RDONLY);
	dup2(fd, 0);
}

static void	loop_her(char **new, char **line, char ***environ, char *stop)
{
	t_hist	*list;

	if (!(list = (t_hist*)malloc(sizeof(t_hist))))
		return ;
	list->histo = NULL;
	while (*new == NULL || ft_strcmp(*new, stop) != 0)
	{
		ft_putcolor("heredoc> ", LIGHT_BLUE);
		ft_setenv("PROMPT", "9", environ);
		ft_strdel(new);
		*new = ft_move(&list, environ);
		if (ft_strcmp(*new, stop) != 0)
		{
			*line = ft_strjoindel(*line, *new);
			*line = ft_strjoindel(*line, "\n");
		}
		ft_putchar('\n');
	}
	free(list);
}

void		heredoc(char ***stock, int i, char ***environ)
{
	char	*line;
	char	*stop;
	char	*new;

	if ((*stock)[i + 1] == NULL)
		ft_puterror("Error: parse error.");
	else
	{
		new = NULL;
		line = ft_strnew(10);
		stop = ft_strdup((*stock)[i + 1]);
		loop_her(&new, &line, environ, stop);
		ft_strdel(&stop);
		ft_strdel(&((*stock)[i]));
		ft_strdel(&((*stock)[i + 1]));
		(*stock)[i] = NULL;
		(*stock)[i + 1] = NULL;
		create_heredoc(line);
		ft_strdel(&line);
		ft_strdel(&new);
	}
}
