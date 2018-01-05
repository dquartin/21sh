/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:51:46 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/13 10:23:45 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		unsetint(char **environ, int i, char *tmp)
{
	if (environ[i][0] == tmp[0] && ft_strstr(environ[i], tmp) != NULL)
	{
		ft_strdel(&environ[i]);
		while (environ[i + 1] != '\0')
		{
			environ[i] = environ[i + 1];
			i++;
		}
		return (1);
	}
	return (0);
}

void	error_case(char *name)
{
	ft_putstrerror("Error: ");
	ft_putstrerror(name);
	ft_puterror(" doesn't exist in env.🤦🏻‍♀️ ");
}

char	**cpy_semitab(char **environ, int i, char *tmp)
{
	char	**semitab;

	environ[i - 1] = NULL;
	ft_strdel(&tmp);
	semitab = ft_envcpy(environ);
	delete_lines(environ);
	return (semitab);
}

char	**ft_unsetenv(char *name, char **environ)
{
	int		i;
	int		cpt;
	char	**semitab;
	char	*tmp;

	i = 0;
	cpt = 0;
	if (!name)
	{
		ft_puterror("Error: Unsetenv takes a name as argument.🤷🏻");
		return (environ);
	}
	tmp = ft_strdup(name);
	tmp = ft_touppercase(tmp);
	tmp = ft_strjoindel(tmp, "=");
	while (environ[i])
	{
		if ((unsetint(environ, i, tmp)) == 1)
			cpt = 1;
		i++;
	}
	semitab = cpy_semitab(environ, i, tmp);
	if (cpt == 0)
		error_case(name);
	return (semitab);
}
