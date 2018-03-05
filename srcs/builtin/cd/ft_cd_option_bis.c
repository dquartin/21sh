/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_option_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 16:36:48 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 16:41:07 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	cd_back_loop(char **tmp, char **path, char ***environ)
{
	char	*tmp1;

	ft_strdel(tmp);
	*tmp = NULL;
	tmp1 = ft_getenv(*environ, "PWD");
	*tmp = ft_strsub(tmp1, 0, ft_strlen(tmp1)
			- ft_strlen(ft_strrchr(tmp1, '/')));
	chdir(*tmp);
	ft_setenv("PWD", *tmp, environ);
	ft_strdel(&tmp1);
	ft_strdel(tmp);
	*tmp = NULL;
	*path = ft_strstr(*path, "../") ?
		ft_strdup(ft_strstr(*path, "../") + 3) :
		ft_strdup(ft_strstr(*path, "..") + 2);
}

void	cd_back_bis(char *tmp, char **path, char ***environ)
{
	tmp = ft_strdup(*path);
	ft_strdel(path);
	*path = ft_strjoin("/Users/", tmp);
	ft_setenv("PWD", *path, environ);
	ft_strdel(&tmp);
}
