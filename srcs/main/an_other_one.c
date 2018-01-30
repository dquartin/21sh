/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   an_other_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 13:21:08 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 17:03:30 by hlely            ###   ########.fr       */
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
}

void	main_check_line(t_all **all, char ***environ, t_truct **str)
{
	if ((*all)->line[0] != '\0')
	{
		init_line(&((*all)->line), environ, &((*str)->list), &((*str)->tree));
		if (ft_strcmp("exit", (*all)->line) == 0)
		{
			if_exit(*environ, &((*all)->paths), &((*str)->list));
			exit(0);
		}
		call_major(&((*all)->paths), &((*all)->stock),
				&((*str)->tree), environ);
		ft_strdel(&((*all)->line));
	}
}
