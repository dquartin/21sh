/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_n_paste.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:26:49 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/02 13:39:35 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	paste_at_end(char **line, int *i, int *x, char *cpy)
{
	*line = ft_realloc(*line, *x, *x + ft_strlen(cpy));
	*x = *x + ft_strlen(cpy);
	*line = ft_strcat(*line, cpy);
	ft_putstrin(cpy);
	ft_strdel(&cpy);
	*i = *x;
}

void	copy_n_paste(char **line, int *i, int *x, char ***environ)
{
	char	*cpy;
	char	*new;

	if ((cpy = ft_getenv(*environ, "COPY")) != NULL)
	{
		if (*i == *x)
			paste_at_end(line, i, x, cpy);
		else
		{
			new = ft_strnew(*x + ft_strlen(cpy));
			new = ft_strncpy(new, *line, *i);
			new = ft_strcat(new, cpy);
			new = ft_strcat(new, ((*line) + *i));
			ft_strdel(line);
			*line = ft_strdup(new);
			ft_strdel(&new);
			ft_putstrin(cpy);
			*i = *i + ft_strlen(cpy);
			*x = *x + ft_strlen(cpy);
			ft_strdel(&cpy);
		}
	}
}

void	copy_select(char *stock, int *x, char ***environ)
{
	int		j;

	j = 0;
	if (stock[0] == '\0')
		ft_putstrin(stock);
	while (j < *x && stock[j] == '\0')
		j++;
	ft_setenv("COPY", stock + j, environ);
}

void	copy_char(char *line, int *i, char **stock)
{
	char	tmp;

	tmp = line[(*i) - 1];
	tputs(tgetstr("le", NULL), 0, ft_putin);
	tputs(tgetstr("dc", NULL), 0, ft_putin);
	if ((*stock)[(*i) - 1] == '\0')
	{
		(*stock)[(*i) - 1] = tmp;
		ft_putstrin("\033[7m");
		ft_putin(tmp);
		ft_putstrin("\033[m");
	}
	else
	{
		(*stock)[(*i) - 1] = '\0';
		ft_putin(line[(*i) - 1]);
	}
}
