/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 15:35:45 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:35:19 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	open_files(char **arr, int i, int fd)
{
	if (arr[i][2] == '>')
		fd = open(arr[i + 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		fd = open(arr[i + 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	arr[i][1] = '\0';
	double_redir(arr, i, fd);
}

int		other(char **arr, int i, int *fd)
{
	if (i - 1 < 0 || arr[i][2] == '\0')
	{
		ft_puterror("Error: parse error");
		return (0);
	}
	arr[i][3] = '\0';
	*fd = ft_atoi(arr[i] + 2);
	return (1);
}
