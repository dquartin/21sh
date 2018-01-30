/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 10:31:48 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:36:45 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	parse_quote(char ***stock)
{
	int		i;
	int		j;

	i = 0;
	while ((*stock)[i])
	{
		j = 0;
		while ((*stock)[i][j])
		{
			if ((*stock)[i][j] == '"' || (*stock)[i][j] == '\'')
			{
				j++;
				while ((*stock)[i][j] != '"' && (*stock)[i][j] != '\''
				&& (*stock)[i][j + 1])
				{
					(*stock)[i][j - 1] = (*stock)[i][j];
					j++;
				}
				(*stock)[i][j] = '\0';
				ft_puterror((*stock)[i]);
			}
			j++;
		}
		i++;
	}
}
