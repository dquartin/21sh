/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:29:05 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:12:48 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int			env_len(char **env)
{
	int		i;

	i = 0;
	if (env)
	{
		while (env[i])
			i++;
	}
	return (i);
}

char		**ft_envcpy(char **env)
{
	char	**environ;
	int		i;

	i = 0;
	CHECKMC(environ = (char**)malloc(sizeof(char*) * (env_len(env) + 1)));
	while (env[i])
	{
		environ[i] = ft_strdup(env[i]);
		i++;
	}
	environ[i] = NULL;
	return (environ);
}

void		ft_print_env(char ***environ)
{
	int		i;

	i = 0;
	while ((*environ)[i])
	{
		ft_putendl((*environ)[i]);
		i++;
	}
}

static void	ft_env_u(char ***environ, char **stock, char **paths)
{
	int		i;
	char	**env;

	i = 0;
	env = NULL;
	if (stock[2])
	{
		env = ft_envcpy(*environ);
		env = ft_unsetenv(stock[2], env);
		if (!(stock[3]))
			ft_print_env(&env);
		else
			call_function(stock + 3, paths, &env, 0);
	}
	else
	{
		g_status = 0;
		ERROR("env: option requires an argument -- u");
	}
	if (env)
	{
		delete_lines(&env);
		free(env);
	}
	env = NULL;
}

void		ft_env(char ***environ, char **stock, char **paths)
{
	char	**array;

	if (!(array = (char**)malloc(sizeof(char*) * 1)))
		return ;
	array[0] = NULL;
	if (stock[1] != '\0')
	{
		if (ft_strcmp(stock[1], "--help") == 0)
			help_env();
		else if (ft_strcmp(stock[1], "-u") == 0)
			ft_env_u(environ, stock, paths);
		else if (ft_strcmp(stock[1], "-i") == 0)
		{
			if (stock[2])
				call_function(stock + 2, paths, &array, 0);
		}
		else if (ft_strchr(stock[1], '=') != NULL)
			ft_env_launch(stock, environ, paths);
		else
			call_function(stock + 1, paths, environ, 0);
		free(array);
		return ;
	}
	free(array);
	ft_print_env(environ);
}
