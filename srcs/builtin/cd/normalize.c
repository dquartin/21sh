/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 10:22:54 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 16:47:44 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

static t_int	*newint(int i)
{
	t_int	*list;

	if (!(list = (t_int*)malloc(sizeof(t_int))))
		return (NULL);
	list->index = i;
	list->next = NULL;
	return (list);
}

static void		addindex(t_int **list, int i)
{
	t_int	*begin;
	t_int	*new;

	new = newint(i);
	if (*list == NULL)
		*list = new;
	else
	{
		begin = *list;
		while ((*list)->next)
			*list = (*list)->next;
		(*list)->next = new;
		*list = begin;
	}
}

static int		get_len(char *pwd)
{
	int		i;
	t_int	*list;
	t_int	*begin;

	i = 0;
	list = NULL;
	while (pwd[i])
	{
		if (pwd[i] == '/')
			addindex(&list, i);
		i++;
	}
	begin = list;
	while (list && list->next && list->next->next)
		list = list->next;
	i = list->index;
	while (begin)
	{
		list = begin;
		begin = begin->next;
		free(list);
	}
	return (i);
}

void			normalize_pwd(char ***environ, int i)
{
	int		j;
	char	*pwd;
	char	*newpwd;
	char	*dot;

	pwd = ft_getenv(*environ, "PWD");
	if (!pwd)
		return ;
	while ((dot = ft_strdup(ft_strstr(pwd, ".."))))
	{
		newpwd = ft_strsub(pwd, 0, ft_strlen(pwd) - ft_strlen(dot));
		j = get_len(newpwd);
		j = (j) ? j : j + 1;
		newpwd = ft_strsubdel(newpwd, 0, j);
		while (dot[i] && dot[i] != '/')
			i++;
		ft_strdel(&pwd);
		pwd = ft_strjoindel(newpwd, dot + i);
		ft_strdel(&dot);
	}
	if (ft_strlen(pwd) > 1 && pwd[ft_strlen(pwd) - 1] == '/')
		pwd[ft_strlen(pwd) - 1] = '\0';
	ft_setenv("PWD", pwd, environ);
	ft_strdel(&pwd);
}
