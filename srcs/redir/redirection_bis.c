/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 10:16:18 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 14:36:58 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int		reverse_bis(char **arr, int i, int *fd)
{
	if (access(arr[i + 1], F_OK) == 0)
	{
		if (access(arr[i + 1], R_OK) == 0)
			*fd = open(arr[i + 1], O_RDONLY);
		else
		{
			ERROR("Permission denied.");
			return (0);
		}
	}
	else
	{
		ft_putstrerror("Error: no such file or directory: ");
		ft_putendl_fd(arr[i + 1], 2);
		return (0);
	}
	return (1);
}

int		closing_redir(char **arr, int i)
{
	int		fd;

	if (arr[i][3] == LESS)
	{
		arr[i][1] = '\0';
		close(ft_atoi(arr[i]));
		return (-1);
	}
	else
	{
		arr[i][4] = '\0';
		fd = ft_atoi(arr[i] + 3);
		return (fd);
	}
}

void	double_redir(char **arr, int i, int fd)
{
	if (arr[i][0] == AND)
	{
		dup2(fd, 1);
		dup2(fd, 2);
	}
	else
		dup2(fd, ft_atoi(arr[i]));
}

void	close_all(char **arr, int i)
{
	if (arr[i][0] == AND)
	{
		close(1);
		close(2);
	}
	else if (arr[i][0] == SIMPLE_RED && arr[i][1] == AND)
		close(1);
}

void	open_file(char **arr, int i, int fd)
{
	if (arr[i][1] == SIMPLE_RED && arr[i][0] == SIMPLE_RED)
		fd = open(arr[i + 1], APPEND);
	else
		fd = open(arr[i + 1], TRUNC);
	dup2(fd, 1);
}
