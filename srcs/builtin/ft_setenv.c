/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:51:45 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:31:37 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static void	setenvint(char ***environ, int i, char *tmp, char *value)
{
	*environ = ft_realloc(*environ, (sizeof(char*) *
	(env_len(*environ) + 1)), (sizeof(char*) * (env_len(*environ) + 2)));
	(*environ)[i] = ft_strjoindel(tmp, value);
}

static int	remplaceenv(char ***environ, char *tmp, char *value, int i)
{
	int		cpt;

	cpt = 1;
	ft_strdel(&((*environ)[i]));
	(*environ)[i] = ft_strjoindel(tmp, value);
	return (cpt);
}

void		ft_setenv(char *name, char *value, char ***environ)
{
	int		i;
	int		cpt;
	char	*tmp;

	i = 0;
	cpt = 0;
	if (!name || !value)
	{
		ft_putstrerror("Error: Setenv function takes a name");
		ft_puterror(" and a value as argument.🤷🏻‍♀️ ");
		return ;
	}
	tmp = ft_strdup(name);
	tmp = ft_touppercase(tmp);
	tmp = ft_strjoindel(tmp, "=");
	while ((*environ)[i])
	{
		if ((*environ)[i][0] == tmp[0] && ft_strstr((*environ)[i], tmp) != NULL)
			cpt = remplaceenv(environ, tmp, value, i);
		i++;
	}
	if (cpt == 0)
		setenvint(environ, i, tmp, value);
}
