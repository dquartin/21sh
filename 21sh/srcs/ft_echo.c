/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:49:30 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/13 10:19:41 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	print_echo(char **stock, int i, int j)
{
	j = 0;
	while (stock[i][j])
	{
		if (stock[i][j] != '"')
			ft_putchar(stock[i][j]);
		j++;
	}
	if (stock[i + 1] != NULL)
		ft_putchar(' ');
}

void	ft_echo(char **stock)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (ft_strcmp(stock[i], "-n") == 0)
	{
		i++;
		while (stock[i])
		{
			print_echo(stock, i, j);
			i++;
		}
	}
	else
	{
		while (stock[i])
		{
			print_echo(stock, i, j);
			i++;
		}
		ft_putchar('\n');
	}
}
