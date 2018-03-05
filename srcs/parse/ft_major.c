/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_major.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:08:10 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:45:44 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	handle_and(t_tree *tree, char ***paths, char ***stock, char ***environ)
{
	g_status = 1;
	ft_major(tree->left, paths, stock, environ);
	if (g_status == 1)
	{
		if (*paths)
		{
			delete_lines(paths);
			free(*paths);
		}
		if (*stock)
		{
			delete_lines(stock);
			free(*stock);
		}
		ft_major(tree->right, paths, stock, environ);
	}
}

void	handle_or(t_tree *tree, char ***paths, char ***stock, char ***environ)
{
	g_status = 1;
	ft_major(tree->left, paths, stock, environ);
	if (g_status == 0)
	{
		if (*paths)
		{
			delete_lines(paths);
			free(*paths);
		}
		if (*stock)
		{
			delete_lines(stock);
			free(*stock);
		}
		ft_major(tree->right, paths, stock, environ);
	}
}

int		handle_data(t_tree *tree, char ***paths, char ***stock, char ***environ)
{
	int		quote;
	int		i;

	i = 0;
	quote = 0;
	if (ft_strchr(tree->content, '"') != NULL)
		quote = 1;
	*paths = split_paths(*paths, *environ);
	if ((*stock = ft_splitwhite(tree->content)) == NULL)
		return (0);
	parse_alias(&((*stock)[0]));
	if (*stock[0] == NULL)
		return (0);
	if ((check_redir(*stock, environ)) == 0)
		return (0);
	call_function(*stock, *paths, environ, quote);
	normalize_pwd(environ, i);
	return (1);
}

void	handle_semicolon(t_tree *tree, char ***paths, char ***stock,
		char ***environ)
{
	ft_major(tree->left, paths, stock, environ);
	if (*paths)
	{
		delete_lines(paths);
		free(*paths);
	}
	if (*stock)
	{
		delete_lines(stock);
		free(*stock);
	}
	waitall(g_nbproc);
	g_nbproc = 0;
	ft_major(tree->right, paths, stock, environ);
}

void	handle_pipe(t_tree *tree, char ***stock, char ***paths, char ***environ)
{
	int		pipefd[2];
	pid_t	father;

	pipe(pipefd);
	g_nbproc++;
	father = fork();
	if (father == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		ft_major(tree->left, paths, stock, environ);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		ft_major(tree->right, paths, stock, environ);
		close(pipefd[0]);
	}
}
