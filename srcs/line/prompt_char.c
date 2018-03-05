/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 12:26:05 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:45:46 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	*promptchar(char *buffer, t_index **index)
{
	if ((*index)->x % 10000 == 0)
		(*index)->line = ft_realloc((*index)->line,
				(int)ft_strlen((*index)->line),
				(int)(ft_strlen((*index)->line) + 10000));
	write(0, &buffer[0], 1);
	(*index)->x++;
	return ((*index)->line);
}

void	get_prompt(t_index **index)
{
	char			*tmp;

	tmp = ft_getenv((*index)->environ, "PROMPT");
	(*index)->prompt = ft_atoi(tmp);
	ft_strdel(&tmp);
}

void	insertchar(t_index **index, char *buffer)
{
	struct winsize	size;
	int				j;

	ioctl(0, TIOCGWINSZ, &size);
	get_prompt(index);
	j = 0;
	while ((*index)->x > (*index)->i)
	{
		(*index)->line[(*index)->x] = (*index)->line[(*index)->x - 1];
		(*index)->x--;
	}
	(*index)->line[(*index)->i] = buffer[0];
	(*index)->x = ft_strlen((*index)->line);
	(*index)->i++;
	if ((*index)->i < (*index)->x)
	{
		if (CHECKSIZE((*index)->i) == 0)
			GO(DOWN);
		GO("sc");
		GO("ei");
		ft_putstrin((*index)->line + (*index)->i);
		GO("im");
		GO("rc");
	}
	(*index)->i--;
}
