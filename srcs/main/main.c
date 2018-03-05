/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:46:03 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 16:25:22 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

extern t_alias	*g_alias;
extern t_hist	*g_list;
extern int		g_status;
extern int		g_heredoc;
extern int		g_nbproc;

void	call_function(char **stock, char **paths, char ***environ, int quote)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	if (ft_strcmp(stock[0], "--help") == 0)
		ft_putstr("usage: [functions] [options] [arguments ...]\n");
	else if (ft_strcmp(stock[0], "history") == 0)
		cmd_history(stock);
	else if (ft_strcmp(stock[0], "env") == 0)
		ft_env(environ, stock, paths);
	else if (ft_strcmp(stock[0], "setenv") == 0)
		set_up_setenv(name, value, stock, environ);
	else if (ft_strcmp(stock[0], "unsetenv") == 0)
		*environ = ft_unsetenv(stock[1], *environ);
	else if (ft_strcmp(stock[0], "cd") == 0)
		*environ = ft_cd(stock, environ);
	else if (ft_strcmp(stock[0], "echo") == 0)
		ft_echo(stock, quote);
	else if (ft_strcmp(stock[0], "alias") == 0)
		handle_alias(stock);
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
	if (buff == NULL || !ft_strchr(buff, '/'))
	{
		ERROR("Oops, there's a probleme with PWD. 😰");
		ERROR("No problem dude, I'll put you in \"/Users\"! 💁");
		ft_setenv("pwd", "/Users", environ);
		chdir("/Users");
		buff = getcwd(buff, 200);
	}
	tmp = ft_strdup(ft_strrchr(buff, '/') + 1);
	ft_strdel(&buff);
	search_prompt(tmp);
	tmp2 = ft_itoa(ft_strlen(tmp) + 5);
	ft_strdel(&tmp);
	SETPROMPT(tmp2);
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
	if (environ[0])
		environ = get_shlvl(environ);
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
			{
				g_status = 0;
				return ;
			}
			dup2(stin, 0);
			dup2(stout, 1);
		}
		call_handle(tree, paths, stock, environ);
	}
}

int		main(int ac, char **av, char **env)
{
	char	pwd[200];
	char	**environ;
	t_all	*all;
	t_truct	*str;

	if (!isatty(STDIN_FILENO))
		exit_atty();
	alloc(&all, &str, &environ);
	ac > 1 ? read_script(av, env) : 0;
	set_null(&(str->tree), &all, &g_list, ac);
	g_list = init_list(&environ, av, env, &(str->std));
	g_alias = init_alias(environ);
	ft_setenv("PWD", getcwd(pwd, 200), &environ);
	g_nbproc = 0;
	while (all->line == NULL || ft_strcmp("exit", all->line) != 0)
	{
		set_std(str->std, &(all->line), &environ);
		set_terminal(all, &environ);
		main_check_line(&all, &environ, &str);
		waitall(g_nbproc);
		g_nbproc = 0;
	}
	return (0);
}
