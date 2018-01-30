/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_major.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 15:08:10 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:43:47 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int		handle_data(t_tree *tree, char ***paths, char ***stock, char ***environ)
{
	int		quote;

	quote = 0;
	if (ft_strchr(tree->content, '"') != NULL)
		quote = 1;
	*paths = split_paths(*paths, *environ);
	*stock = ft_splitwhite(tree->content);
	parse_quote(stock);
	if (*stock[0] == NULL)
		return (0);
	if ((check_redir(*stock, environ)) == 0)
		return (0);
	call_function(*stock, *paths, environ, quote);
	return (1);
}

void	handle_semicolon(t_tree *tree, char ***paths, char ***stock,
		char ***environ)
{
	ft_major(tree->left, paths, stock, environ);
	delete_lines(paths);
	free(*paths);
	delete_lines(stock);
	free(*stock);
	ft_major(tree->right, paths, stock, environ);
}

void	handle_pipe(t_tree *tree, char ***stock, char ***paths, char ***environ)
{
	int		pipefd[2];
	pid_t	father;

	pipe(pipefd);
	father = fork();
	if (father == 0)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		ft_major(tree->left, paths, stock, environ);
		exit(0);
	}
	else
	{
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		ft_major(tree->right, paths, stock, environ);
	}
}
