/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 08:59:49 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:45:08 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	delete_lines(char ***stock)
{
	int		i;

	i = 0;
	while ((*stock)[i])
	{
		ft_strdel((*stock) + i);
		i++;
	}
}

void	delinline(t_index **index)
{
	int		j;

	j = (*index)->i;
	while ((*index)->line[j])
	{
		(*index)->line[j - 1] = (*index)->line[j];
		j++;
	}
	(*index)->line[j - 1] = '\0';
}

void	delchar(t_index **index)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	if ((*index)->i > 0)
	{
		GO(LEFT);
		GO(CLR);
		delinline(index);
		if (CHECKSIZE((*index)->i) == 0)
		{
			GO(LEFT);
			GO(SUP);
			GO(SUP);
			ft_putchar((*index)->line[(*index)->i - 2]);
			GO(RIGHT);
		}
		GO(CLR);
		GO("sc");
		GO("ei");
		ft_putstrin((*index)->line + (*index)->i - 1);
		GO("im");
		GO("rc");
	}
}

void	call_delchar(t_index **index)
{
	while ((*index)->x > 0)
	{
		GO(LEFT);
		GO(SUP);
		delinline(index);
		(*index)->x--;
		(*index)->i--;
	}
}

void	begin(t_index **index)
{
	if ((*index)->i > 0)
	{
		delchar(index);
		(*index)->x--;
		(*index)->i--;
	}
}
