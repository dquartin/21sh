/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:21:51 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:50:17 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	**cd_less(char ***environ, char *buff)
{
	char	*ret;
	char	*tmp;

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
	return (*environ);
}

char	**cd_p(char ***environ, char *option, char *buff)
{
	char	*tmp;
	char	*path_tmp;

	tmp = NULL;
	path_tmp = NULL;
	ft_setenv("OLD_DIR", getcwd(buff, 200), environ);
	if (option)
	{
		path_tmp = ft_strdup(option);
		if (chdir(path_tmp) == -1)
			error_case1(path_tmp);
		ft_setenv("PWD", getcwd(buff, 200), environ);
	}
	else
	{
		if ((tmp = ft_getenv(*environ, "HOME")) == 0)
			tmp = ft_strdup("/");
		path_tmp = ft_strdup(tmp);
		if (chdir(path_tmp) == -1)
			error_case1(path_tmp);
		ft_setenv("PWD", getcwd(buff, 200), environ);
	}
	ft_strdel(&tmp);
	ft_strdel(&path_tmp);
	return (*environ);
}

char	**cd_back(char ***environ)
{
	char	*tmp;
	char	*tmp1;

	if ((tmp = ft_getenv(*environ, "PWD")) == 0)
		tmp = getcwd(tmp, 200);
	ft_setenv("OLD_DIR", tmp, environ);
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
	return (*environ);
}

char	**cd_l(char ***environ, char **path, char *option)
{
	char	*tmp;
	char	*path_tmp;
	char	buff[200];

	tmp = NULL;
	path_tmp = NULL;
	path++;
	ft_setenv("OLD_DIR", getcwd(buff, 200), environ);
	if (option)
		path_tmp = ft_strdup(option);
	else
	{
		if ((tmp = ft_getenv(*environ, "HOME")) == 0)
			tmp = ft_strdup("/");
		path_tmp = ft_strdup(tmp);
	}
	cd_l_bis(environ, &path_tmp, buff);
	ft_strdel(&path_tmp);
	if (tmp)
		ft_strdel(&tmp);
	return (*environ);
}

void	cd(char ***environ, char **path, char *buff)
{
	char	*tmp;
	char	*tmp2;
	int		free;

	free = 0;
	tmp = NULL;
	buff = NULL;
	if ((*path)[0] != '/')
	{
		if ((tmp = ft_getenv(*environ, "PWD")) == NULL)
			tmp = getcwd(buff, 200);
		tmp = ft_strjoindel(tmp, "/");
		tmp2 = ft_strdup(*path);
		*path = ft_strjoindel(tmp, tmp2);
		free = 1;
		ft_strdel(&tmp2);
	}
	tmp2 = getcwd(buff, 200);
	if ((chdir(*path)) == -1)
		ERROR("Error: not a directory.");
	else
		set_old_dir(tmp2, path, environ);
	ft_strdel(&tmp2);
	free ? ft_strdel(path) : 0;
}
