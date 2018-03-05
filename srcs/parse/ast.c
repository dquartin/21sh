/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:00:01 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:15:57 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

t_tree			*create_node(void)
{
	t_tree	*tree;

	CHECKMC(tree = (t_tree*)malloc(sizeof(t_tree)));
	tree->right = 0;
	tree->left = 0;
	tree->content = 0;
	return (tree);
}

static void		parse_semi(t_tree **tree, char *line, int size, int i)
{
	(*tree)->type = SEMICOLON;
	(*tree)->left = create_node();
	(*tree)->right = create_node();
	while (line[i] && i < size && line[i] != SEMI)
		i++;
	parse(&(*tree)->right, line + i + 1, size - i - 1);
	parse(&(*tree)->left, line, i);
}

static void		parse_and(t_tree **tree, char *line, int size)
{
	int		i;

	(*tree)->type = ET;
	(*tree)->right = create_node();
	(*tree)->left = create_node();
	i = 0;
	while (line[i] && i < size && (line[i] != AND || line[i + 1] != AND))
		i++;
	parse(&(*tree)->right, line + i + 2, size - i - 2);
	parse(&(*tree)->left, line, i);
}

void			parse(t_tree **tree, char *line, int size)
{
	int		j;

	if (ft_strchr(line, SEMI) && ft_strchr(line, SEMI) < line + size
			&& check_quote(line, SEMI, &j, size))
		parse_semi(tree, line, size, j);
	else if (ft_strnrstr(line, "||", size) > ft_strnrstr(line, "&&", size))
		parse_or(tree, line, size);
	else if (ft_strnrstr(line, "&&", size))
		parse_and(tree, line, size);
	else if (ft_strchr(line, TUBE) && ft_strchr(line, TUBE) < line + size
			&& check_quote(line, TUBE, &j, size))
		parse_pipe(tree, line, size, j);
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
