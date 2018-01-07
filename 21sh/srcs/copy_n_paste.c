/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_n_paste.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:26:49 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/07 12:41:03 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	paste_at_end(t_index **index, char *cpy)
{
	(*index)->line = ft_realloc((*index)->line,
		(*index)->x, (*index)->x + ft_strlen(cpy));
	(*index)->x = (*index)->x + ft_strlen(cpy);
	(*index)->line = ft_strcat((*index)->line, cpy);
	ft_putstrin(cpy);
	ft_strdel(&cpy);
	(*index)->i = (*index)->x;
}

void	copy_n_paste(t_index **index)
{
	char	*cpy;
	char	*new;

	if ((cpy = ft_getenv((*index)->environ, "COPY")) != NULL)
	{
		if ((*index)->i == (*index)->x)
			paste_at_end(index, cpy);
		else
		{
			new = ft_strnew((*index)->x + ft_strlen(cpy));
			new = ft_strncpy(new, (*index)->line, (*index)->i);
			new = ft_strcat(new, cpy);
			new = ft_strcat(new, ((*index)->line + (*index)->i));
			ft_strdel(&(*index)->line);
			(*index)->line = ft_strdup(new);
			ft_strdel(&new);
			ft_putstrin(cpy);
			(*index)->i = (*index)->i + ft_strlen(cpy);
			(*index)->x = (*index)->x + ft_strlen(cpy);
			ft_strdel(&cpy);
		}
	}
}

void	copy_select(char *stock, t_index **index)
{
	int		j;

	j = 0;
	if (stock[0] == '\0')
		ft_putstrin(stock);
	while (j < (*index)->x && stock[j] == '\0')
		j++;
	ft_setenv("COPY", stock + j, &(*index)->environ);
}

void	copy_char(t_index **index, char **stock)
{
	char	tmp;

	tmp = (*index)->line[(*index)->i - 1];
	tputs(tgetstr("le", NULL), 0, ft_putin);
	tputs(tgetstr("dc", NULL), 0, ft_putin);
	if ((*stock)[(*index)->i - 1] == '\0')
	{
		(*stock)[(*index)->i - 1] = tmp;
		ft_putstrin("\033[7m");
		ft_putin(tmp);
		ft_putstrin("\033[m");
	}
	else
	{
		(*stock)[(*index)->i - 1] = '\0';
		ft_putin((*index)->line[(*index)->i - 1]);
	}
}
