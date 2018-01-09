/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 12:00:01 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/08 16:21:42 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_tree    *create_node(void)
{
	t_tree    *tree;

	if (!(tree = (t_tree*)malloc(sizeof(t_tree))))
		return (NULL);
	tree->right = 0;
	tree->left = 0;
	tree->content = 0;
	return (tree);
}

void    parse(t_tree **tree, char *line, int size)
{
	int        i;

	if (ft_strchr(line, ';') && ft_strchr(line, ';') < line + size)
	{
		(*tree)->type = SEMICOLON;
		(*tree)->left = create_node();
		(*tree)->right = create_node();
		i = 0;
		while (line[i] && i < size && line[i] != ';')
			i++;
		parse(&(*tree)->right, line + i + 1, size - i - 1);
		parse(&(*tree)->left, line, i);
	}
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

t_tree    *new_parser(char *line)
{
	t_tree    *tree;

	tree = create_node();
	parse(&tree, line, ft_strlen(line));
	return (tree);
}

/*
   t_tree		*create_tree(t_tree *tree, char *line, int i)
   {
   if (!tree)
   {
   if (!(tree = (t_tree*)malloc(sizeof(t_tree))))
   return (NULL);
   }
   if (!(tree->right = (t_tree*)malloc(sizeof(t_tree))))
   return (NULL);
   if (!(tree->left = (t_tree*)malloc(sizeof(t_tree))))
   return (NULL);
   tree->right->com = ft_strnew(10000);
   tree->left->com = ft_strnew(10000);
   while (line[i])
   {
   if (line[i] == ';' || line[i] == '|' || line[i] == '>')
   {
   tree->c = line[i];
   i++;
   while ((line[i] != ';' && line[i] != '|' && line[i] != '>') && line[i])
   {
   tree->left->com = ft_strncat(tree->left->com, line + i, 1);
   i++;
   }
   tree->left->c = line[i];
   tree->left = create_tree(tree->left, line, i + 1);
   return (tree);
   }
   tree->right->com = ft_strncat(tree->right->com, line + i, 1);
   i++;
   }
   return (tree);
   }*/
