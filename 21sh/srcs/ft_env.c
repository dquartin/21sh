/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:29:05 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/13 10:19:54 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**ft_envcpy(char **env)
{
	char	**environ;
	int		i;

	i = 0;
	if (!(environ = (char**)malloc(sizeof(char*) * (env_len(env) + 1))))
		return (NULL);
	while (env[i])
	{
		environ[i] = ft_strdup(env[i]);
		i++;
	}
	environ[i] = NULL;
	return (environ);
}

void	ft_env(char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		ft_putendl(environ[i]);
		i++;
	}
}
