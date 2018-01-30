/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:46:14 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 15:55:53 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

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
	if (father == 0)
		execve(stock[0], stock, environ);
	if (father > 0)
	{
		waitpid(father, &father, 0);
		handle_segv(father);
	}
}

void	fork_bis(char **environ, char **paths, char **stock)
{
	int		i;

	i = 0;
	signal(18, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrl_c);
	if (!environ[0])
		exit(0);
	while (paths[i])
	{
		call_execve(i, stock, paths, environ);
		i++;
	}
	ft_puterror("Error: no such command. 🙄");
}

void	call_fork(char **stock, char **paths, char **environ)
{
	struct termios	term;
	pid_t			father;

	tcgetattr(0, &term);
	term.c_lflag = (ICANON | ECHO | ISIG);
	tcsetattr(0, 0, &term);
	if (ft_strcmp(stock[0], "exit") != 0)
	{
		father = fork();
		if (father == 0)
		{
			fork_bis(environ, paths, stock);
			exit(0);
		}
		if (father > 0)
		{
			signal(18, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, ctrl_c_bis);
			waitpid(father, &father, 0);
			handle_segv(father);
		}
	}
}
