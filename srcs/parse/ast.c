/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:00:01 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/30 10:45:27 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static t_tree	*create_node(void)
{
	t_tree	*tree;

	if (!(tree = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	tree->right = 0;
	tree->left = 0;
	tree->content = 0;
	return (tree);
}

static void		parse_semi(t_tree **tree, char *line, int size)
{
	int		i;

	(*tree)->type = SEMICOLON;
	(*tree)->left = create_node();
	(*tree)->right = create_node();
	i = 0;
	while (line[i] && i < size && line[i] != ';')
		i++;
	parse(&(*tree)->right, line + i + 1, size - i - 1);
	parse(&(*tree)->left, line, i);
}

void			parse(t_tree **tree, char *line, int size)
{
	int		i;

	if (ft_strchr(line, ';') && ft_strchr(line, ';') < line + size)
		parse_semi(tree, line, size);
	else if (ft_strchr(line, '|') && ft_strchr(line, '|') < line + size)
	{
		(*tree)->type = PIPE;
		(*tree)->left = create_node();
		(*tree)->right = create_node();
		i = 0;
		while (line[i] && i < size && line[i] != '|')
			i++;
		parse(&(*tree)->right, line + i + 1, size - i - 1);
		parse(&(*tree)->left, line, i);
	}
	else
	{
		(*tree)->type = DATA;
		(*tree)->content = ft_strnew(size + 1);
		(*tree)->content = ft_strncpy((*tree)->content, line, size);
	}
}

t_tree			*new_parser(char *line)
{
	t_tree	*tree;

	tree = create_node();
	parse(&tree, line, ft_strlen(line));
	return (tree);
}
