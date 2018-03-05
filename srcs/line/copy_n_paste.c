/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_n_paste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:00:28 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 15:48:54 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static void	paste_at_end(t_index **index, char *cpy)
{
	(*index)->line = ft_realloc((*index)->line,
			(*index)->x, (*index)->x + ft_strlen(cpy));
	(*index)->x = (*index)->x + ft_strlen(cpy);
	(*index)->line = ft_strcat((*index)->line, cpy);
	ft_putstrin(cpy);
	ft_strdel(&cpy);
	(*index)->i = (*index)->x;
}

static void	ft_put_end(char **tmp, t_index **index, char **new)
{
	GO("sc");
	GO(CLR);
	*tmp = ft_strnew(10000);
	*tmp = ft_strncpy(*tmp, (*index)->line, (*index)->i);
	ft_strdel(&(*index)->line);
	(*index)->line = ft_strnew(10000);
	(*index)->line = ft_strcpy((*index)->line, *tmp);
	(*index)->line = ft_strcat((*index)->line, *new);
	ft_putstrin(*new);
	GO("rc");
	ft_strdel(tmp);
}

void		copy_n_paste(t_index **index)
{
	char			*cpy;
	char			*new;
	char			*tmp;
	int				len;
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	if ((cpy = ft_getenv((*index)->environ, "COPY")) != NULL)
	{
		if ((*index)->i == (*index)->x)
			paste_at_end(index, cpy);
		else
		{
			len = ft_strlen(cpy) + (*index)->i;
			new = ft_strnew((*index)->x + ft_strlen(cpy));
			new = ft_strcpy(new, cpy);
			new = ft_strcat(new, ((*index)->line + (*index)->i));
			ft_put_end(&tmp, index, &new);
			while ((*index)->i < len)
				go_to_right(index, size);
			ft_strdel(&new);
			(*index)->x = (*index)->x + ft_strlen(cpy);
			ft_strdel(&cpy);
		}
	}
}

void		copy_select(char *stock, t_index **index)
{
	int		j;

	j = 0;
	if (stock[0] == '\0')
		ft_putstrin(stock);
	while (j < (*index)->x && stock[j] == '\0')
		j++;
	ft_setenv("COPY", stock + j, &(*index)->environ);
}

void		copy_char(t_index **index, char **stock)
{
	char	tmp;

	tmp = (*index)->line[(*index)->i - 1];
	GO(LEFT);
	GO("dc");
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
