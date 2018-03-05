/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:34:17 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:09:11 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static void		add_alias(char **stock)
{
	char	*tmp;

	g_status = 0;
	if (!(stock[2]))
		ERROR("Error: no name given for alias");
	else if (!(stock[3]))
		ERROR("Error: no value given");
	else if (stock[4])
		ERROR("Error: too many arguments");
	else
	{
		if (check_existing_alias(g_alias, stock[2]) == 0)
		{
			ERROR("Error: an alias already exists for this name");
			return ;
		}
		g_status = 1;
		tmp = ft_strjoin(stock[2], "=");
		tmp = ft_strjoindel(tmp, stock[3]);
		if ((g_alias = new_node_alias(g_alias, tmp)) == NULL)
			ERROR("Error: alias can't be created for some reasons");
		ft_strdel(&tmp);
	}
}

static void		remove_alias(char **stock)
{
	t_alias		*alias;

	g_status = 0;
	if (env_len(stock) > 4)
		ERROR("Error: too many arguments");
	if (env_len(stock) <= 2)
		ERROR("Error: no name given");
	else
	{
		alias = g_alias;
		if (alias && ft_strcmp(alias->name, stock[2]) == 0)
			return (remove_alias_bis(alias));
		while (alias && alias->next)
		{
			if (alias->next && ft_strcmp(alias->next->name, stock[2]) == 0)
				return (remove_alias_bisbis(alias));
			alias = alias->next;
		}
		ERROR("Error: no entry for given name");
	}
}

static void		modify_alias(char **stock)
{
	t_alias		*alias;

	g_status = 0;
	if (env_len(stock) > 4)
		ERROR("Error: too many arguments");
	else if (env_len(stock) <= 2)
		ERROR("Error: no name given for alias");
	else if (env_len(stock) <= 3)
		ERROR("Error: no value given");
	else
	{
		alias = g_alias;
		while (alias)
		{
			if (ft_strcmp(stock[2], alias->name) == 0)
			{
				g_status = 1;
				ft_strdel(&(alias->value));
				alias->value = ft_strdup(stock[3]);
				return ;
			}
			alias = alias->next;
		}
		ERROR("Error: no entry for given name");
	}
}

static void		display_alias(void)
{
	t_alias		*alias;

	alias = g_alias;
	while (alias)
	{
		ft_putstr(alias->name);
		ft_putchar('=');
		ft_putendl(alias->value);
		alias = alias->next;
	}
}

void			handle_alias(char **stock)
{
	if (stock[1] && ft_strcmp(stock[1], "-a") == 0)
		add_alias(stock);
	else if (stock[1] && ft_strcmp(stock[1], "-r") == 0)
		remove_alias(stock);
	else if (stock[1] && ft_strcmp(stock[1], "-m") == 0)
		modify_alias(stock);
	else if (stock[1] && stock[1][0] == '-')
	{
		ft_putstrerror("Error: illegal option: ");
		ERROR(stock[1]);
		ERROR("usage: alias [-a name value] [-r name] [-m name value]");
		g_status = 0;
		return ;
	}
	else
		display_alias();
}
