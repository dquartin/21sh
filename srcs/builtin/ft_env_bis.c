/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:00:31 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:13:05 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	help_env(void)
{
	g_status = 0;
	ft_putstr("usage: env [-i] [-u name] [argument ...]\n");
}

void	change_env(char *stock, char ***env)
{
	int		len;
	char	*name;
	char	*value;

	len = ft_strlen(ft_strchr(stock, '=') + 1);
	name = ft_strsub(stock, 0, ft_strlen(stock) - len - 1);
	value = ft_strdup(ft_strchr(stock, '=') + 1);
	ft_setenv(name, value, env);
	ft_strdel(&value);
	ft_strdel(&name);
}

void	ft_env_launch(char **stock, char ***environ, char **paths)
{
	int		i;
	char	**env;

	i = 1;
	env = NULL;
	env = ft_envcpy(*environ);
	while (stock && stock[i] && ft_strchr(stock[i], '='))
	{
		change_env(stock[i], &env);
		i++;
	}
	if (stock[i])
		call_function(stock + i, paths, &env, 0);
	else
		ft_print_env(&env);
	if (env)
	{
		delete_lines(&env);
		free(env);
	}
}
