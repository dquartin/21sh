/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:06:38 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 16:02:46 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	init_line(char **line, char ***environ, t_hist **list, t_tree **tree)
{
	char	c;
	int		stock;

	stock = 0;
	if ((c = ft_analyse(*line)) != 0)
	{
		*line = dquote(*line, c, environ, *list);
		stock = 1;
	}
	*tree = new_parser(*line);
	if (!stock)
		*list = stock_history(*line, *list);
}

void	init_std(t_std **std)
{
	(*std)->stin = dup(0);
	(*std)->stout = dup(1);
	(*std)->sterr = dup(2);
}

void	set_std(t_std *std, char **line, char ***environ)
{
	g_heredoc = 0;
	dup2(std->stin, 0);
	dup2(std->stout, 1);
	dup2(std->sterr, 2);
	ft_strdel(line);
	print_prompt(environ);
}

void	env_null(char ***environ)
{
	if ((*environ)[0] == NULL)
	{
		ERROR("Error: environement is not initialized. Exiting...");
		free(*environ);
		exit(EXIT_FAILURE);
		*environ = set_environ();
	}
}

t_hist	*init_list(char ***environ, char **av, char **env, t_std **std)
{
	t_hist	*list;
	char	*login;

	*environ = cpy_environ(av, env);
	env_null(environ);
	if ((login = ft_getenv(*environ, "USER")) == NULL)
		login = ft_strdup("Unknow_user");
	ft_putstr("Welcome ");
	ft_putstr(login);
	ft_putstr(" !\n");
	ft_strdel(&login);
	init_std(std);
	create_history(environ);
	list = get_history(*environ);
	return (list);
}
