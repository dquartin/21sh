/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 12:12:45 by dquartin          #+#    #+#             */
/*   Updated: 2018/03/01 13:39:33 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int				check_hist_env(char **environ)
{
	if (!(environ[0]))
	{
		ERROR("Environnement not set, can't grab history file");
		g_status = 0;
		return (0);
	}
	return (1);
}

static void		print_history(void)
{
	int		i;

	i = 1;
	while (g_list && g_list->next)
		g_list = g_list->next;
	while (g_list)
	{
		ft_putstr("  ");
		ft_putnbr(i);
		ft_putstr("  ");
		ft_putendl(g_list->histo);
		if (!g_list->prev)
			break ;
		g_list = g_list->prev;
		i++;
	}
}

void			cmd_history(char **stock)
{
	if (env_len(stock) == 1)
		print_history();
	else if (!ft_strcmp(stock[1], "--help"))
		ft_putstr("usage: history to print the history");
	else if (env_len(stock) > 1)
		ERROR("Error: invalid option, use --help");
}
