/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:48:45 by dquartin          #+#    #+#             */
/*   Updated: 2018/03/01 13:57:33 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ctrl_c(int i)
{
	signal(i, SIG_IGN);
	exit(0);
}

void	ctrl_c_bis(int i)
{
	signal(i, SIG_IGN);
	kill(0, i);
}

void	ctrl_d(t_index *index, char buff[])
{
	if (index->line[0] == '\0')
	{
		ft_bzero(buff, 7);
		GO("ei");
		SAVETERM;
		if (!g_heredoc)
			exit(0);
		g_heredoc = 2;
	}
}

char	*ctrl_c_move(t_index *index, char buff[])
{
	char			*line;
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	end(&index, size);
	ft_bzero(buff, 7);
	ft_strdel(&(index->line));
	delete_lines(&(index->environ));
	free(index->environ);
	ft_lst_clear(&(index->start));
	free(index);
	line = ft_strnew(100);
	return (line);
}

void	handle_segv(pid_t fath)
{
	if (!WIFEXITED(fath))
	{
		if (WIFSIGNALED(fath))
		{
			(WTERMSIG(fath) == SIGABRT) ? ERROR("21sh : Abort") : 0;
			(WTERMSIG(fath) == SIGBUS) ? ERROR("21sh : Bus error") : 0;
			(WTERMSIG(fath) == SIGSEGV) ?
				ERROR("21sh : Segmentation fault") : 0;
		}
	}
}
