/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:59:26 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:27:39 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void		error_case1(char *path)
{
	ft_putstrerror("Error: ");
	if (path)
		ft_putstrerror(path);
	ft_puterror(": no such file or directory.");
}

static void	error_case2(char *path)
{
	ft_putstrerror("Error: ");
	if (path)
		ft_putstrerror(path);
	ft_puterror(": permission denied.");
}

static char	**ft_cd_bis(char *path, char *option, char ***environ, char *buff)
{
	if (ft_strcmp(path, "..") == 0)
		return (cd_back(environ, buff));
	if (ft_strcmp(path, "-") == 0)
		return (cd_less(environ, buff));
	if (ft_strcmp(path, "-L") == 0)
		cd_l(environ, &path, option);
	if (ft_strcmp(path, "-P") == 0)
		return (cd_p(environ, option, path, buff));
	return (NULL);
}

static void	ft_set_path(char **tmp, char **path, char **option, char ***environ)
{
	*tmp = ft_getenv(*environ, "HOME");
	*path = ft_strdup(*tmp);
	*option = ft_strdup("1");
}

char		**ft_cd(char *path, char *option, char ***environ)
{
	char	*tmp;
	char	*buff;

	tmp = NULL;
	buff = ft_strnew(200);
	if (!path)
		ft_set_path(&tmp, &path, &option, environ);
	if (ft_strcmp(path, "--help") == 0)
	{
		ft_putstr("usage: cd [-] [-L] [-P] [argument ...]\n");
		return (*environ);
	}
	if (ft_cd_bis(path, option, environ, buff) != NULL)
		return (*environ);
	else if (access(path, F_OK | X_OK) == 0)
		cd(environ, &path, option, buff);
	else if (access(path, F_OK) == -1)
		error_case1(path);
	else if (access(path, X_OK) == -1)
		error_case2(path);
	if (tmp)
		ft_strdel(&tmp);
	ft_strdel(&buff);
	return (*environ);
}
