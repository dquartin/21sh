/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 14:18:54 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:44:23 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	**set_environ(void)
{
	char	**env;
	char	buff[200];
	char	*tmp;

	if (!(env = (char**)malloc(sizeof(char*) * 5)))
		return (NULL);
	tmp = ft_strjoin("PWD=", getcwd(buff, 200));
	env[0] = ft_strdup(tmp);
	env[1] = ft_strdup("HOME=/Users");
	env[2] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/usr/local/bin");
	env[3] = ft_strdup("USER=unknown_user");
	env[4] = NULL;
	ft_strdel(&tmp);
	return (env);
}
