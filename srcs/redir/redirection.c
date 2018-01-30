/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:30:44 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:35:01 by dquartin         ###   ########.fr       */
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

	if (i - 1 < 0 || arr[i + 1] == NULL)
	{
		ft_puterror("Error: parse error");
		return (0);
	}
	if (arr[i][1] != '<')
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
	if (arr[i][2] == '-')
		close_all(arr, i);
	else
	{
		if (arr[i][1] == '&')
		{
			if ((other(arr, i, &fd)) == 0)
				return (0);
		}
		else if (i - 1 < 0 || arr[i + 1] == NULL)
		{
			ft_puterror("Error: parse error");
			return (0);
		}
		open_file(arr, i, fd);
	}
	if (arr[i][2] != '-')
		delete_from_tab(&arr, i);
	delete_from_tab(&arr, i);
	return (1);
}

int		advanced_redir(char **arr, int i)
{
	int		fd;

	fd = 0;
	if (arr[i][2] == '-')
		close_all(arr, i);
	if (arr[i][0] == '&' && arr[i][2] == '>' && arr[i][1] == '>')
		return (ft_puterror("Error: parse error"));
	if (arr[i][2] == '&' && i - 1 >= 0)
	{
		if ((fd = closing_redir(arr, i)) == -1)
		{
			delete_from_tab(&arr, i);
			return (1);
		}
	}
	else if (i - 1 < 0 || arr[i + 1] == NULL)
		return (ft_puterror("Error: parse error"));
	open_files(arr, i, fd);
	if (arr[i][2] != '&')
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
		if (arr[i][0] == '<')
		{
			if ((reverse_redir(arr, i, env)) == 0)
				return (0);
		}
		else if (arr[i][0] == '>')
		{
			if ((simple_redir(arr, i)) == 0)
				return (0);
		}
		else if (arr[i][1] == '>')
		{
			if ((advanced_redir(arr, i)) == 0)
				return (0);
		}
		else
			i++;
	}
	return (1);
}
