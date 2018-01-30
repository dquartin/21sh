/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 17:49:30 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:31:08 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static void	ft_echo_q(char **stock, int *i)
{
	int		j;

	while (stock[*i])
	{
		j = 0;
		while (stock[*i][j])
		{
			if (stock[*i][j] == '\\' && stock[*i][j + 1] == 'n')
			{
				ft_putchar('\n');
				j++;
			}
			else
				ft_putchar(stock[*i][j]);
			j++;
		}
		if (stock[*i + 1] != NULL)
			ft_putchar(' ');
		(*i)++;
	}
}

static void	ft_echo_nq(char **stock, int *i)
{
	int		j;

	while (stock[*i])
	{
		j = 0;
		while (stock[*i][j])
		{
			if (stock[*i][j] != '\\')
				ft_putchar(stock[*i][j]);
			j++;
		}
		if (stock[*i + 1] != NULL)
			ft_putchar(' ');
		(*i)++;
	}
}

static void	ft_echo_n(char **stock, int quote, int *i)
{
	int		j;

	(*i)++;
	if (quote == 1)
		ft_echo_q(stock, i);
	else
		ft_echo_nq(stock, i);
	(*i)--;
	j = ft_strlen(stock[*i]);
}

void		ft_echo(char **stock, int quote)
{
	int		i;

	i = 1;
	if (stock[i] == NULL)
	{
		ft_putstr("\n");
		return ;
	}
	if (ft_strcmp(stock[i], "--help") == 0)
		ft_putstr("usage: echo [-n] [argument ...]\n");
	else if (ft_strcmp(stock[i], "-n") == 0)
		ft_echo_n(stock, quote, &i);
	else
	{
		if (quote == 1)
			ft_echo_q(stock, &i);
		else
			ft_echo_nq(stock, &i);
		ft_putchar('\n');
	}
}
