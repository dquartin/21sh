/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 15:50:50 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:31:29 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char	*ft_getenv(char **env, char *elem)
{
	int		i;
	char	*comp;
	char	*ret;

	i = 0;
	while (env[i])
	{
		comp = ft_strndup(env[i], '=');
		if (ft_strcmp(comp, elem) == 0)
		{
			ret = ft_strsub(env[i], (ft_strlen(comp) + 1), ft_strlen(env[i]));
			ft_strdel(&comp);
			return (ret);
		}
		ft_strdel(&comp);
		i++;
	}
	return (0);
}
