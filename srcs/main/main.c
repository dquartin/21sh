/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 14:02:56 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 17:02:32 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	call_function(char **stock, char **paths, char ***environ, int quote)
{
	int		i;

	i = 0;
	if (ft_strcmp(stock[0], "--help") == 0)
		ft_putstr("usage: [functions] [options] [arguments ...]\n");
	else if (ft_strcmp(stock[0], "env") == 0)
		ft_env(environ, stock, paths);
	else if (ft_strcmp(stock[0], "setenv") == 0)
		ft_setenv(stock[1], stock[2], environ);
	else if (ft_strcmp(stock[0], "unsetenv") == 0)
		*environ = ft_unsetenv(stock[1], *environ);
	else if (ft_strcmp(stock[0], "cd") == 0)
		*environ = ft_cd(stock[1], stock[2], environ);
	else if (ft_strcmp(stock[0], "echo") == 0)
		ft_echo(stock, quote);
	else if (access(stock[0], X_OK | F_OK) == 0)
		exec_path(stock, *environ);
	else
		call_fork(stock, paths, *environ);
}

void	print_prompt(char ***environ)
{
	char	**stock;
	char	*buff;
	char	*tmp;
	char	*tmp2;

	stock = NULL;
	buff = ft_getenv(*environ, "PWD");
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
	tmp2 = ft_itoa(ft_strlen(tmp) + 5);
	ft_setenv("PROMPT", tmp2, environ);
	ft_strdel(&tmp2);
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

void	ft_major(t_tree *tree, char ***paths, char ***stock, char ***environ)
{
	int		i;
	int		stin;
	int		stout;
	int		quote;

	i = 0;
	quote = 0;
	stin = dup(0);
	stout = dup(1);
	if (tree)
	{
		if (tree->type == DATA)
		{
			if (handle_data(tree, paths, stock, environ) == 0)
				return ;
			dup2(stin, 0);
			dup2(stout, 1);
		}
		if (tree->type == SEMICOLON)
			handle_semicolon(tree, paths, stock, environ);
		if (tree->type == PIPE)
			handle_pipe(tree, stock, paths, environ);
	}
}

int		main(int ac, char **av, char **env)
{
	char	**environ;
	t_all	*all;
	t_truct	*str;
	pid_t	father;

	alloc(&all, &str, &environ);
	ac > 1 ? read_script(av, env) : 0;
	father = fork();
	if (father)
		set_signal_father(father);
	else
	{
		set_null(&(str->tree), &all, &(str->list), ac);
		str->list = init_list(&environ, av, env, &(str->std));
		while (all->line == NULL || ft_strcmp("exit", all->line) != 0)
		{
			set_std(str->std, &(all->line), &environ);
			set_terminal(all, str, &environ);
			str->term.c_lflag = (ISIG);
			ft_putchar('\n');
			main_check_line(&all, &environ, &str);
		}
		exit(0);
	}
	return (0);
}
