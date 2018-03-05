/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 15:56:54 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 13:31:50 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	**split_semicolon(char *line)
{
	char **stock;

	stock = ft_strsplit(line, ';');
	if (line)
		ft_strdel(&line);
	return (stock);
}

char	**split_paths(char **paths, char **environ)
{
	char	*path;

	path = ft_getenv(environ, "PATH");
	paths = ft_strsplit(path, ':');
	ft_strdel(&path);
	return (paths);
}
