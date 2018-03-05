/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_alias.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:35:13 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:17:05 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	parse_alias(char **stock)
{
	t_alias		*alias;

	alias = g_alias;
	if (!stock || !stock[0])
		return ;
	while (alias)
	{
		if (ft_strncmp(*stock, alias->name, ft_strlen(alias->name)) == 0
			&& (*stock)[ft_strlen(alias->name)] == '\0')
		{
			*stock = ft_strreplace(*stock, alias->value,
					ft_strlen(alias->name));
			return ;
		}
		alias = alias->next;
	}
}
