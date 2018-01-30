/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:21:51 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:27:55 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	**cd_less(char ***environ, char *buff)
{
	char	*ret;
	char	*tmp;

	ft_strdel(&buff);
	buff = ft_strnew(200);
	buff = getcwd(buff, 200);
	if ((tmp = ft_getenv(*environ, "OLD_DIR")) != 0)
	{
		ft_strdel(&tmp);
		ret = ft_getenv(*environ, "OLD_DIR");
		ft_setenv("OLD_DIR", buff, environ);
		chdir(ret);
		ft_setenv("PWD", ret, environ);
		ft_strdel(&ret);
		getcwd(buff, 200);
		ft_putendl(buff);
	}
	ft_strdel(&buff);
	return (*environ);
}

char	**cd_p(char ***environ, char *option, char *path, char *buff)
{
	char	*tmp;

	tmp = NULL;
	ft_setenv("OLD_DIR", getcwd(buff, 200), environ);
	if (option)
	{
		ft_strdel(&path);
		path = ft_strdup(option);
		if (chdir(path) == -1)
			error_case1(path);
		ft_setenv("PWD", getcwd(buff, 200), environ);
	}
	else
	{
		tmp = ft_getenv(*environ, "HOME");
		ft_strdel(&path);
		path = ft_strdup(tmp);
		if (chdir(path) == -1)
			error_case1(path);
		ft_setenv("PWD", getcwd(buff, 200), environ);
	}
	if (tmp)
		ft_strdel(&tmp);
	ft_strdel(&buff);
	return (*environ);
}

char	**cd_back(char ***environ, char *buff)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_getenv(*environ, "PWD");
	if (ft_strrchr(tmp + 1, '/') == NULL)
	{
		chdir("/");
		ft_setenv("PWD", "/", environ);
	}
	else
	{
		ft_strdel(&tmp);
		tmp1 = ft_getenv(*environ, "PWD");
		tmp = ft_strsub(tmp1, 0, ft_strlen(tmp1)
		- ft_strlen(ft_strrchr(tmp1, '/')));
		chdir(tmp);
		ft_setenv("PWD", tmp, environ);
		ft_strdel(&tmp1);
	}
	if (tmp)
		ft_strdel(&tmp);
	ft_strdel(&buff);
	return (*environ);
}

void	cd_l(char ***environ, char **path, char *option)
{
	char	*tmp;

	tmp = NULL;
	if (option)
	{
		ft_strdel(path);
		*path = ft_strdup(option);
	}
	else
	{
		tmp = ft_getenv(*environ, "HOME");
		ft_strdel(path);
		*path = ft_strdup(tmp);
	}
	if (tmp)
		ft_strdel(&tmp);
}

void	cd(char ***environ, char **path, char *option, char *buff)
{
	char	*tmp;
	char	*tmp2;
	int		free;

	free = 0;
	tmp = NULL;
	buff = NULL;
	if ((*path)[0] != '/')
	{
		tmp = ft_getenv(*environ, "PWD");
		tmp = ft_strjoindel(tmp, "/");
		tmp2 = ft_strdup(*path);
		*path = ft_strjoindel(tmp, tmp2);
		free = 1;
		ft_strdel(&tmp2);
	}
	tmp2 = getcwd(buff, 200);
	ft_setenv("OLD_DIR", tmp2, environ);
	chdir(*path);
	ft_setenv("PWD", *path, environ);
	ft_strdel(&tmp2);
	del_opt_path(&option, path);
	if (free)
		ft_strdel(path);
}
