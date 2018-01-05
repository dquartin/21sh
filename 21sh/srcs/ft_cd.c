/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:59:26 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/13 17:00:17 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	**cd_less(char ***environ)
{
	char	*ret;
	char	*tmp;
	char	*buff;

	buff = NULL;
	buff = getcwd(buff, 200);
	if ((tmp = ft_getenv(*environ, "OLD_DIR")) != 0)
	{
		ft_strdel(&tmp);
		ret = ft_getenv(*environ, "OLD_DIR");
		ft_setenv("OLD_DIR", buff, environ);
		chdir(ret);
		ft_strdel(&ret);
	}
	ft_strdel(&buff);
	return (*environ);
}

void	error_case1(char *path)
{
	ft_putstrerror("Error: ");
	if (path)
		ft_putstrerror(path);
	ft_puterror(" no such file or directory.");
}

void	error_case2(char *path)
{
	ft_putstrerror("Error: ");
	if (path)
		ft_putstrerror(path);
	ft_puterror(" permission denied.");
}

char	**ft_cd(char *path, char ***environ)
{
	char	*tmp;
	char	buff[200];

	tmp = NULL;
	if (!path)
	{
		tmp = ft_getenv(*environ, "HOME");
		path = tmp;
	}
	if (ft_strcmp(path, "-") == 0)
	{
		ft_strdel(&tmp);
		return (cd_less(environ));
	}
	if (access(path, F_OK | X_OK) == 0)
	{
		ft_setenv("OLD_DIR", getcwd(buff, 200), environ);
		chdir(path);
	}
	else if (access(path, F_OK) == -1)
		error_case1(path);
	else if (access(path, X_OK) == -1)
		error_case2(path);
	ft_strdel(&tmp);
	return (*environ);
}
