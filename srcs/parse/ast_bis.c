/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:13:41 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:16:28 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	loop_check(char *line, int *i, int size)
{
	if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] && *i < size && line[*i] != '"')
			(*i)++;
	}
	else if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && *i < size && line[*i] != '\'')
			(*i)++;
	}
}

int		check_quote(char *line, char c, int *j, int size)
{
	int		i;

	i = 0;
	*j = 0;
	if (!ft_strchr(line, '\'') && !ft_strchr(line, '"'))
		return (1);
	while (line[i] && i < size)
	{
		if (line[i] == c)
			return (1);
		loop_check(line, &i, size);
		i++;
		*j = i;
	}
	return (0);
}

void	parse_or(t_tree **tree, char *line, int size)
{
	int		i;

	(*tree)->type = OU;
	(*tree)->right = create_node();
	(*tree)->left = create_node();
	i = 0;
	while (line[i] && i < size && (line[i] != TUBE | line[i + 1] != TUBE))
		i++;
	parse(&(*tree)->right, line + i + 2, size - i - 2);
	parse(&(*tree)->left, line, i);
}

void	parse_pipe(t_tree **tree, char *line, int size, int i)
{
	(*tree)->type = PIPE;
	(*tree)->left = create_node();
	(*tree)->right = create_node();
	while (line[i] && i < size && line[i] != TUBE)
		i++;
	parse(&(*tree)->right, line + i + 1, size - i - 1);
	parse(&(*tree)->left, line, i);
}
