/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:57:30 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 13:58:05 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	search_prompt(char *tmp)
{
	if (g_status == 1)
	{
		ft_putcolor("➜ ", LIGHT_MAGENTA);
		ft_putcolor(tmp, LIGHT_BLUE);
		ft_putcolor("$> ", LIGHT_MAGENTA);
	}
	else
	{
		ft_putcolor("➜ ", LIGHT_RED);
		ft_putcolor(tmp, WHITE);
		ft_putcolor("$> ", LIGHT_RED);
	}
	g_status = 1;
}

char	**get_shlvl(char **environ)
{
	char	*shlvl;
	int		lvl;

	shlvl = NULL;
	lvl = 0;
	if ((shlvl = ft_getenv(environ, "SHLVL")) == NULL)
	{
		ft_setenv("shlvl", "1", &environ);
		shlvl = ft_strdup("1");
	}
	lvl = ft_atoi(shlvl);
	lvl++;
	ft_strdel(&shlvl);
	shlvl = ft_itoa(lvl);
	ft_setenv("SHLVL", shlvl, &environ);
	ft_strdel(&shlvl);
	return (environ);
}
