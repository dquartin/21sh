/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 09:35:10 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:44:46 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	delete_alias(t_alias *alias, char **env)
{
	t_alias *tmp;
	int		fd;
	char	*tmp2;

	if ((tmp2 = ft_getenv(env, "HOME")) == 0)
		return ;
	tmp2 = ft_strjoindel(tmp2, "/.alias");
	fd = open(tmp2, TRUNC);
	while (alias != NULL)
	{
		ft_putstr_fd(alias->name, fd);
		ft_putstr_fd("=", fd);
		ft_putendl_fd(alias->value, fd);
		ft_strdel(&(alias->name));
		ft_strdel(&(alias->value));
		tmp = alias;
		alias = alias->next;
		free(tmp);
	}
	ft_strdel(&tmp2);
	close(fd);
}
