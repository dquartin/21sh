/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_return.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 10:26:49 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 16:35:54 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int		return_dot(char *path, char *option)
{
	if (path && !ft_strcmp(path, "."))
	{
		ft_strdel(&path);
		ft_strdel(&option);
		return (1);
	}
	return (0);
}

int		return_cd_bis(char *path, char *option, char ***environ, char buff[])
{
	if (ft_cd_bis(path, option, environ, buff) != NULL)
	{
		ft_strdel(&path);
		ft_strdel(&option);
		return (1);
	}
	return (0);
}

void	set_old_dir(char *tmp2, char **path, char ***environ)
{
	ft_setenv("OLD_DIR", tmp2, environ);
	ft_setenv("PWD", *path, environ);
}
