/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:51:46 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:14:04 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static int	unsetint(char **environ, int i, char *tmp)
{
	if (environ[i][0] == tmp[0] &&
	ft_strnstr(environ[i], tmp, ft_strlen(tmp) + 1) != NULL)
	{
		ft_strdel(&(environ[i]));
		while (environ[i + 1] != '\0')
		{
			environ[i] = environ[i + 1];
			i++;
		}
		return (1);
	}
	return (0);
}

static void	error_case(char *name)
{
	g_status = 0;
	ft_putstrerror("Error: ");
	ft_putstrerror(name);
	ERROR(" doesn't exist in env.🤦🏻‍♀️ ");
}

static char	**cpy_semitab(char **environ, int i, char *tmp)
{
	char	**semitab;

	environ[i - 1] = NULL;
	ft_strdel(&tmp);
	semitab = ft_envcpy(environ);
	delete_lines(&environ);
	free(environ);
	environ = NULL;
	return (semitab);
}

static void	tiny_loop(char **environ, int *i, int *cpt, char *tmp)
{
	while (environ[*i])
	{
		if ((unsetint(environ, *i, tmp)) == 1)
			*cpt = 1;
		(*i)++;
	}
}

char		**ft_unsetenv(char *name, char **environ)
{
	int		i;
	int		cpt;
	char	**semitab;
	char	*tmp;

	i = 0;
	cpt = 0;
	semitab = NULL;
	if (!name)
	{
		error_unsetenv();
		return (environ);
	}
	tmp = ft_strdup(name);
	tmp = ft_touppercase(tmp);
	tmp = ft_strjoindel(tmp, "=");
	tiny_loop(environ, &i, &cpt, tmp);
	if (cpt == 0)
	{
		error_case(name);
		ft_strdel(&tmp);
		return (environ);
	}
	semitab = cpy_semitab(environ, i, tmp);
	return (semitab);
}
