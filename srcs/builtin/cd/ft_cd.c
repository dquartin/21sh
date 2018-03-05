/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 16:59:26 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:39:10 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void		error_case1(char *path)
{
	g_status = 0;
	ft_putstrerror("Error: ");
	if (path)
		ft_putstrerror(path);
	ERROR(": no such file or directory.");
}

void		error_case2(char *path)
{
	g_status = 0;
	ft_putstrerror("Error: ");
	if (path)
		ft_putstrerror(path);
	ERROR(": permission denied.");
}

char		**ft_cd_bis(char *path, char *option, char ***environ, char *buff)
{
	if (ft_strcmp(path, "..") == 0)
		return (cd_back(environ));
	if (ft_strcmp(path, "-") == 0)
		return (cd_less(environ, buff));
	if (ft_strcmp(path, "-L") == 0)
		return (cd_l(environ, &path, option));
	if (ft_strcmp(path, "-P") == 0)
		return (cd_p(environ, option, buff));
	return (NULL);
}

static void	ft_set_path(char **tmp, char **path, char **option, char ***environ)
{
	if ((*tmp = ft_getenv(*environ, "HOME")) == 0)
	{
		ft_putendl("Variable HOME not set, HOME defined to /");
		*tmp = ft_strdup("/");
	}
	*path = ft_strdup(*tmp);
	*option = ft_strdup("1");
}

char		**ft_cd(char **stock, char ***environ)
{
	char	*tmp;
	char	buff[200];
	char	*path;
	char	*option;

	tmp = NULL;
	path = NULL;
	option = NULL;
	if (env_len(stock) >= 2)
		path = ft_strdup(stock[1]);
	if (env_len(stock) >= 3)
		option = ft_strdup(stock[2]);
	if (return_dot(path, option) || error_environ(*environ, path, option))
		return (*environ);
	if (!path)
		ft_set_path(&tmp, &path, &option, environ);
	if (return_usage(path, option))
		return (*environ);
	if (return_cd_bis(path, option, environ, buff))
		return (*environ);
	check_cd(path, environ, buff);
	ft_strdel(&path);
	ft_strdel(&option);
	ft_strdel(&tmp);
	return (*environ);
}
