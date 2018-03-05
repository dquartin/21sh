/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:53:43 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:14:32 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	remove_alias_bis(t_alias *alias)
{
	t_alias		*tmp;

	g_status = 1;
	ft_strdel(&(alias->name));
	ft_strdel(&(alias->value));
	tmp = alias->next;
	free(alias);
	g_alias = tmp;
}

void	remove_alias_bisbis(t_alias *alias)
{
	t_alias		*tmp;

	g_status = 1;
	ft_strdel(&(alias->next->value));
	ft_strdel(&(alias->next->name));
	tmp = alias->next->next;
	free(alias->next);
	alias->next = tmp;
}
