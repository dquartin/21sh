/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 10:58:02 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:22:41 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

extern struct termios	g_save_attr;

void	if_exit(char **environ, char ***paths, char ***stock, t_hist **list)
{
	save_history(*list, environ);
	ft_hst_clear(list);
	delete_alias(g_alias, environ);
	if (*stock)
	{
		delete_lines(stock);
		free(*stock);
	}
	if (*paths)
	{
		delete_lines(paths);
		free(*paths);
	}
	if (environ)
	{
		delete_lines(&environ);
		free(environ);
	}
	ft_putcolor("Good bye ! 🖖\n", WHITE);
}

void	del_paths_n_stock(char ***paths, char ***stock)
{
	if (*paths)
	{
		delete_lines(paths);
		free(*paths);
	}
	if (*stock)
	{
		delete_lines(stock);
		free(*stock);
	}
}

void	set_null(t_tree **tree, t_all **all, t_hist **list, int ac)
{
	(void)ac;
	*tree = NULL;
	(*all)->paths = NULL;
	(*all)->stock = NULL;
	(*all)->line = NULL;
	*list = NULL;
}

void	set_terminal(t_all *all, char ***environ)
{
	struct termios	term;
	char			*tmp;

	signal(18, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	ft_setenv("term", "xterm", environ);
	tmp = ft_getenv(*environ, "TERM");
	tgetent(NULL, tmp);
	ft_strdel(&tmp);
	tcgetattr(0, &g_save_attr);
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	GO("im");
	all->line = ft_move(&g_list, environ);
	GO("ei");
	SAVETERM;
}
