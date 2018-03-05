/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:09:50 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 15:44:58 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	free_index(t_index **index)
{
	delete_lines(&((*index)->environ));
	free((*index)->environ);
	(*index)->environ = NULL;
	ft_strdel(&((*index)->line));
	ft_lst_clear(&((*index)->start));
	if (index)
	{
		free(*index);
		*index = NULL;
	}
}

void	free_tree(t_tree **tree)
{
	if ((*tree)->left)
		free_tree(&((*tree)->left));
	if ((*tree)->right)
		free_tree(&((*tree)->right));
	ft_strdel(&((*tree)->content));
	if (tree)
		free(*tree);
}
