/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:35:45 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 14:37:57 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	open_files(char **arr, int i, int fd)
{
	if (ft_strchr(arr[i], AND) == NULL || arr[i][0] == AND)
	{
		if (arr[i][2] == SIMPLE_RED)
			fd = open(arr[i + 1], APPEND);
		else
			fd = open(arr[i + 1], TRUNC);
		arr[i][1] = '\0';
	}
	double_redir(arr, i, fd);
}

int		other(char **arr, int i, int *fd)
{
	if (i - 1 < 0 || arr[i][2] == '\0')
	{
		ERROR("Error: parse error");
		return (0);
	}
	arr[i][3] = '\0';
	*fd = ft_atoi(arr[i] + 2);
	return (1);
}
