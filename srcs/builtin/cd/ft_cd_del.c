/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 11:14:46 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 16:50:36 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int		return_usage(char *path, char *option)
{
	if (ft_strcmp(path, "--help") == 0)
	{
		ft_putstr("usage: cd [-] [-L] [-P] [argument ...]\n");
		ft_strdel(&path);
		ft_strdel(&option);
		return (1);
	}
	return (0);
}

int		error_environ(char **environ, char *path, char *option)
{
	if ((environ)[0] == NULL)
	{
		ERROR("Error : cd: HOME not set");
		ft_strdel(&path);
		ft_strdel(&option);
		return (1);
	}
	return (0);
}

void	del_opt_path(char **option, char **path)
{
	if (*option && ft_strcmp(*option, "1") == 0)
	{
		ft_strdel(option);
		ft_strdel(path);
	}
}

void	cd_l_bis(char ***environ, char **path, char *buff)
{
	char	*tmp;
	char	*tmp2;
	int		free;

	free = 0;
	tmp = NULL;
	buff = NULL;
	if ((*path)[0] != '/')
	{
		tmp = getcwd(tmp, 200);
		tmp = ft_strjoindel(tmp, "/");
		tmp2 = ft_strdup(*path);
		ft_strdel(path);
		*path = ft_strjoindel(tmp, tmp2);
		free = 1;
		ft_strdel(&tmp2);
	}
	tmp2 = getcwd(buff, 200);
	ft_setenv("OLD_DIR", tmp2, environ);
	chdir(*path);
	ft_setenv("PWD", *path, environ);
	ft_strdel(&tmp2);
}

void	check_cd(char *path, char ***environ, char *buff)
{
	if (path)
	{
		if (access(path, F_OK | X_OK) == 0)
			cd(environ, &path, buff);
		else if (access(path, F_OK) == -1)
			error_case1(path);
		else if (access(path, X_OK) == -1)
			error_case2(path);
	}
}
