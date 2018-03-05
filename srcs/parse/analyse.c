/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:08:12 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/04 15:56:18 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static int	check_bis(char c, char *line, int *i)
{
	if (c == '"' && line[*i] == '"')
		return (1);
	if (c == '\'' && line[*i] == '\'')
		return (1);
	if (c == '(' && line[*i] == ')')
		return (1);
	if (c == '{' && line[*i] == '}')
		return (1);
	if (c == '[' && line[*i] == ']')
		return (1);
	return (0);
}

static int	check(char *line, char c)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (line[i])
	{
		if (c != '[' && line[i] == ']')
			return (0);
		if (c != '(' && line[i] == ')')
			return (0);
		if (c != '{' && line[i] == '}')
			return (0);
		if (check_bis(c, line, &i))
			return (i);
		if (line[i] == '"' || line[i] == '\'')
		{
			if ((j = check(line + i, line[i])) == 0)
				return (0);
			i = i + j;
		}
		i++;
	}
	return (0);
}

char		ft_analyse(char *line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ']' || line[i] == ')' || line[i] == '}')
			return (0);
		if (line[i] == '"' || line[i] == '\'' || line[i] == '['
				|| line[i] == '{' || line[i] == '(')
		{
			if ((j = check(line + i, line[i])) == 0)
				return (line[i]);
			i = i + j;
		}
		i++;
	}
	return (0);
}
