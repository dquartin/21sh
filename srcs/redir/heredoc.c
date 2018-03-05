/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 10:32:24 by dquartin          #+#    #+#             */
/*   Updated: 2018/03/01 14:07:59 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static void	create_heredoc(char *line)
{
	int		fd;

	if (access(".heredoc", F_OK) == 0)
		fd = open(".heredoc", O_WRONLY | O_TRUNC);
	else
		fd = open(".heredoc", O_CREAT | O_WRONLY, 0644);
	write(fd, line, ft_strlen(line));
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	dup2(fd, 0);
}

void		set_termios(void)
{
	struct termios	term;

	tcgetattr(0, &term);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	term.c_lflag = ~(ICANON | ECHO | ISIG);
	tcsetattr(0, TCSANOW, &term);
}

static void	loop_her(char **new, char **line, char ***environ, char *stop)
{
	t_hist			*list;

	if (!(list = (t_hist*)malloc(sizeof(t_hist))))
		return ;
	list->histo = NULL;
	while ((*new == NULL || ft_strcmp(*new, stop) != 0) && g_heredoc != 2)
	{
		ft_putstrin("heredoc> ");
		SETPROMPT("9");
		ft_strdel(new);
		g_heredoc = 1;
		set_termios();
		*new = ft_move(&list, environ);
		SAVETERM;
		if (ft_strcmp(*new, stop) != 0)
		{
			*line = ft_strjoindel(*line, *new);
			*line = (g_heredoc != 2 ? ft_strjoindel(*line, "\n") : *line);
		}
	}
	free(list);
}

void		heredoc(char ***stock, int i, char ***environ)
{
	char	*line;
	char	*stop;
	char	*new;

	if ((*stock)[i + 1] == NULL)
		ERROR("Error: parse error.");
	else
	{
		new = NULL;
		line = ft_strnew(10);
		stop = ft_strdup((*stock)[i + 1]);
		loop_her(&new, &line, environ, stop);
		ft_strdel(&stop);
		create_heredoc(line);
		ft_strdel(&line);
		ft_strdel(&new);
	}
}
