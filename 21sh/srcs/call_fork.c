/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:46:14 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/13 10:41:45 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	call_execve(int i, char **stock, char **paths, char **environ)
{
	char	*path;

	path = NULL;
	if (access(path, F_OK) != 0)
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoindel(path, stock[0]);
	}
	execve(path, stock, environ);
	ft_strdel(&path);
}

void	exec_path(char **stock, char **environ)
{
	pid_t father;

	father = fork();
	if (father > 0)
		wait(0);
	if (father == 0)
		execve(stock[0], stock, environ);
}

void	call_fork(char **stock, char **paths, char **environ)
{
	pid_t	father;
	int		i;

	if (ft_strcmp(stock[0], "exit") != 0)
	{
		father = fork();
		if (father > 0)
			wait(0);
		if (father == 0)
		{
			i = 0;
			if (!ft_getenv(environ, "PATH"))
			{
				ft_puterror("Error: PATH is not initialized. 😱");
				exit(0);
			}
			while (paths[i])
			{
				call_execve(i, stock, paths, environ);
				i++;
			}
			ft_puterror("Error: no such command. 🙄");
			exit(0);
		}
	}
}
