/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   an_other_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:21:08 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/12 11:25:59 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	read_script(char **av, char **env)
{
	pid_t	father;

	if (ft_strstr(av[1], "sh"))
	{
		father = fork();
		if (father == 0)
		{
			execve(av[1], NULL, env);
			exit(0);
		}
		else
			wait(0);
	}
}

void	call_major(char ***paths, char ***stock, t_tree **tree, char ***environ)
{
	del_paths_n_stock(paths, stock);
	ft_major(*tree, paths, stock, environ);
	free_tree(tree);
}

void	alloc(t_all **all, t_truct **str, char ***environ)
{
	if (!(*all = (t_all*)malloc(sizeof(t_all))))
		return ;
	if (!(*str = (t_truct*)malloc(sizeof(t_truct))))
		return ;
	if (!((*str)->std = (t_std*)malloc(sizeof(t_std))))
		return ;
	*environ = NULL;
	g_list = NULL;
	g_status = 1;
}

void	main_check_line(t_all **all, char ***environ, t_truct **str)
{
	ft_putchar('\n');
	if ((*all)->line[0] != '\0')
	{
		init_line(&((*all)->line), environ, &g_list, &((*str)->tree));
		if (ft_strcmp("exit", (*all)->line) == 0)
		{
			if_exit(*environ, &((*all)->paths), &((*all)->stock), &g_list);
			ft_strdel(&(*all)->line);
			free(*all);
			free((*str)->std);
			delete_tree(&((*str)->tree));
			free(*str);
			exit(0);
		}
		call_major(&((*all)->paths), &((*all)->stock),
				&((*str)->tree), environ);
		ft_strdel(&((*all)->line));
	}
}

void	call_handle(t_tree *tree, char ***paths, char ***stock, char ***environ)
{
	if (tree->type == ET)
		handle_and(tree, paths, stock, environ);
	if (tree->type == OU)
		handle_or(tree, paths, stock, environ);
	if (tree->type == SEMICOLON)
		handle_semicolon(tree, paths, stock, environ);
	if (tree->type == PIPE)
		handle_pipe(tree, stock, paths, environ);
}
