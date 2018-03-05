/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:30:44 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 14:55:50 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	delete_from_tab(char ***arr, int i)
{
	ft_strdel((*arr) + i);
	while ((*arr)[i + 1])
	{
		(*arr)[i] = (*arr)[i + 1];
		i++;
	}
	(*arr)[i] = 0;
}

int		reverse_redir(char **arr, int i, char ***env)
{
	int		fd;

	if (PARSE_ERROR)
	{
		ERROR("Parse Error");
		return (0);
	}
	if (arr[i][1] != REVERSE_RED)
	{
		if ((reverse_bis(arr, i, &fd)) == 0)
			return (0);
		dup2(fd, 0);
		delete_from_tab(&arr, i);
		delete_from_tab(&arr, i);
	}
	else
	{
		heredoc(&arr, i, env);
		delete_from_tab(&arr, i);
		delete_from_tab(&arr, i);
	}
	return (1);
}

int		simple_redir(char **arr, int i)
{
	int		fd;

	fd = 0;
	if (ft_strlen(arr[i]) >= 3 && arr[i][2] == LESS)
		close_all(arr, i);
	else
	{
		if (ft_strlen(arr[i]) >= 2 && arr[i][1] == AND)
		{
			if ((other(arr, i, &fd)) == 0)
				return (0);
		}
		else if (PARSE_ERROR)
		{
			ERROR("Error: parse error");
			return (0);
		}
		open_file(arr, i, fd);
	}
	if (ft_strlen(arr[i]) <= 2 || arr[i][2] != LESS)
		delete_from_tab(&arr, i);
	delete_from_tab(&arr, i);
	return (1);
}

int		advanced_redir(char **arr, int i)
{
	int		fd;

	fd = 0;
	if (arr[i][2] == LESS)
		close_all(arr, i);
	if (arr[i][0] == AND && arr[i][2] == SIMPLE_RED &&
		arr[i][1] == SIMPLE_RED)
		return (ERROR("Error: parse error"));
	if (arr[i][2] == AND && i - 1 >= 0)
	{
		if ((fd = closing_redir(arr, i)) == -1)
		{
			delete_from_tab(&arr, i);
			return (1);
		}
	}
	else if (PARSE_ERROR)
		return (ERROR("Error: parse error"));
	open_files(arr, i, fd);
	if (arr[i][2] != AND)
		delete_from_tab(&arr, i);
	delete_from_tab(&arr, i);
	return (1);
}

int		check_redir(char **arr, char ***env)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		if (arr[i][0] == REVERSE_RED)
		{
			if ((reverse_redir(arr, i, env)) == 0)
				return (0);
		}
		else if (arr[i][0] == SIMPLE_RED)
		{
			if ((simple_redir(arr, i)) == 0)
				return (0);
		}
		else if (arr[i][0] && arr[i][1] == SIMPLE_RED)
		{
			if ((advanced_redir(arr, i)) == 0)
				return (0);
		}
		else
			i++;
	}
	return (1);
}
