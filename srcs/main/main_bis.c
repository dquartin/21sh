/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 10:58:02 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:25:30 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	if_exit(char **environ, char ***paths, t_hist **list)
{
	save_history(*list, environ);
	if (*paths)
		delete_lines(paths);
	if (environ)
		delete_lines(&environ);
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

void	set_signal_father(pid_t father)
{
	signal(18, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c_bis);
	waitpid(father, 0, 0);
}

void	set_terminal(t_all *all, t_truct *str, char ***environ)
{
	struct termios	term;

	signal(18, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
	tgetent(NULL, getenv("TERM"));
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	tputs(tgetstr("im", NULL), 100, ft_putin);
	all->line = ft_move(&(str->list), environ);
	tputs(tgetstr("ei", NULL), 100, ft_putin);
}
