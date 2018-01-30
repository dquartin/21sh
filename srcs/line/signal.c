/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 14:48:45 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:45:40 by dquartin         ###   ########.fr       */
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
	struct termios term;

	if (index->line[0] == '\0')
	{
		ft_bzero(buff, 7);
		tputs(tgetstr("ei", NULL), 1, ft_putin);
		tcgetattr(0, &term);
		term.c_lflag = (ICANON | ECHO);
		tcsetattr(0, 0, &term);
		exit(0);
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
			(WTERMSIG(fath) == SIGABRT) ? ft_putstr("21sh : Abort\n") : 0;
			(WTERMSIG(fath) == SIGBUS) ? ft_putstr("21sh : Bus error\n") : 0;
			(WTERMSIG(fath) == SIGSEGV) ?
				ft_putstr("21sh : Segmentation fault\n") : 0;
		}
	}
}
