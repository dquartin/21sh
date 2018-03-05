/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:46:14 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:21:42 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	call_execve(int i, char **stock, char **paths, char **environ)
{
	char	*path;

	path = NULL;
	path = ft_strjoin(paths[i], "/");
	path = ft_strjoindel(path, stock[0]);
	execve(path, stock, environ);
	ft_strdel(&path);
}

void	exec_path(char **stock, char **environ)
{
	pid_t	father;

	g_nbproc++;
	father = fork();
	if (father == 0)
	{
		signal(18, SIG_IGN);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execve(stock[0], stock, environ);
	}
}

void	fork_bis(char **environ, char **paths, char **stock)
{
	int		i;
	char	*tmp;

	i = 0;
	signal(18, SIG_IGN);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	tmp = ft_getenv(environ, "PATH");
	if (tmp == NULL)
	{
		ERROR("Error: PATH is not initialized.");
		exit(1);
	}
	ft_strdel(&tmp);
	while (paths[i])
	{
		call_execve(i, stock, paths, environ);
		i++;
	}
	ERROR("Error: no such command. 🙄");
	exit(1);
}

void	call_fork(char **stock, char **paths, char **environ)
{
	pid_t			father;

	SAVETERM;
	if (ft_strcmp(stock[0], "exit") != 0)
	{
		g_nbproc++;
		father = fork();
		if (father == 0)
		{
			fork_bis(environ, paths, stock);
			exit(0);
		}
	}
}
