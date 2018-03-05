/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:15:16 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 16:40:25 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	cpy_path_opt(char **path, char **option, char **stock)
{
	if (stock[1][0] == LESS)
		*option = ft_strdup(stock[1]);
	else
		*path = ft_strdup(stock[1]);
}

void	change_path_opt(char **path, char **option, char **stock)
{
	ft_strdel(path);
	*path = ft_strdup(stock[2]);
	*option = ft_strdup(stock[1]);
}
