/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:02:56 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/02 11:03:37 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	call_function(char **stock, char **paths, char ***environ)
{
	int		i;

	i = 0;
	if (ft_strcmp(stock[0], "env") == 0)
		ft_env(*environ);
	else if (ft_strcmp(stock[0], "setenv") == 0)
		ft_setenv(stock[1], stock[2], environ);
	else if (ft_strcmp(stock[0], "unsetenv") == 0)
		*environ = ft_unsetenv(stock[1], *environ);
	else if (ft_strcmp(stock[0], "cd") == 0)
		*environ = ft_cd(stock[1], environ);
	else if (ft_strcmp(stock[0], "echo") == 0)
		ft_echo(stock);
	else if (access(stock[0], X_OK | F_OK) == 0)
		exec_path(stock, *environ);
	else
		call_fork(stock, paths, *environ);
	if (paths)
		delete_lines(paths);
	if (stock)
		delete_lines(stock);
}

void	print_prompt(char ***environ)
{
	char	**stock;
	char	*buff;
	char	*tmp;

	stock = NULL;
	buff = NULL;
	buff = getcwd(buff, 200);
	if (buff == NULL)
	{
		ft_puterror("Oops, there's a probleme with path. 😰");
		ft_puterror("No problem dude, I'll put you in \"/Users\"! 💁");
		chdir("/Users");
		buff = getcwd(buff, 200);
	}
	tmp = ft_strrchr(buff, '/') + 1;
	ft_strdel(&buff);
	ft_putcolor("➜ ", LIGHT_MAGENTA);
	ft_putcolor(tmp, LIGHT_BLUE);
	ft_putcolor("$> ", LIGHT_MAGENTA);
	ft_setenv("PROMPT", ft_itoa(ft_strlen(tmp) + 5), environ);
}

char	**cpy_environ(char **av, char **env)
{
	char	**environ;
	pid_t	father;

	father = fork();
	if (father)
		wait(0);
	else
		execve("/usr/bin/clear", av, env);
	environ = ft_envcpy(env);
	return (environ);
}

void	ft_major(char ***semitab, char ***paths, char ***stock, char ***environ)
{
	int		i;

	i = 0;
	if (*semitab)
	{
		while ((*semitab)[i])
		{
			*paths = split_paths(*paths, *environ);
			*stock = ft_splitwhite((*semitab)[i]);
			if (*stock[0] == NULL)
			{
				delete_lines(*stock);
				delete_lines(*semitab);
				delete_lines(*paths);
				return ;
			}
			if (ft_strcmp("exit", (*stock)[0]) == 0)
			{
				ft_putcolor("Good bye ! 🖖\n", WHITE);
				delete_lines(*stock);
				exit(0);
			}
			call_function(*stock, *paths, environ);
			i++;
		}
		delete_lines(*semitab);
	}
}

int		main(int ac, char **av, char **env)
{
	char	*line;
	char	**stock;
	char	**environ;
	char	**paths;
	char	**semitab;
	struct termios	term;
	t_hist	*list;

	paths = NULL;
	line = NULL;
	list = NULL;
	(void)ac;
	environ = cpy_environ(av, env);
	while (line == NULL || ft_strcmp("exit", line) != 0)
	{
		line = NULL;
		semitab = NULL;
		print_prompt(&environ);
		tgetent(NULL, getenv("TERM"));
		tcgetattr(0, &term);
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		tcsetattr(0, TCSADRAIN, &term);
		tputs(tgetstr("im", NULL), 100, ft_putin);
		line = ft_move(&list, &environ);
		list = stock_history(line, list);
		tputs(tgetstr("ei", NULL), 100, ft_putin);
		ft_putchar('\n');
		semitab = split_semicolon(line);
		ft_major(&semitab, &paths, &stock, &environ);
	}
	delete_lines(environ);
	return (0);
}
