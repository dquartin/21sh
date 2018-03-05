/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 10:09:40 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:44:51 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	delete_tree(t_tree **tree)
{
	if ((*tree)->right)
		delete_tree(&(*tree)->right);
	if ((*tree)->left)
		delete_tree(&(*tree)->left);
	ft_strdel(&(*tree)->content);
	free(*tree);
}
