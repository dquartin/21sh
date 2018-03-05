/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:36:21 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:09:09 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static t_alias		*fill_alias(char *line, t_alias *alias)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	alias->name = ft_strsub(line, 0, i);
	alias->value = ft_strsub(line, i + 1, ft_strlen(line) - i - 1);
	alias->next = NULL;
	return (alias);
}

t_alias				*new_node_alias(t_alias *begin, char *line)
{
	t_alias	*alias;

	alias = begin;
	if (alias == NULL)
	{
		CHECKMC(alias = (t_alias*)malloc(sizeof(t_alias)));
		alias = fill_alias(line, alias);
		return (alias);
	}
	else
	{
		while (alias->next)
			alias = alias->next;
		CHECKMC(alias->next = (t_alias*)malloc(sizeof(t_alias)));
		alias->next = fill_alias(line, alias->next);
	}
	return (begin);
}

t_alias				*init_alias(char **env)
{
	char	*file;
	char	*line;
	char	*tmp;
	int		fd;
	t_alias	*alias;

	alias = NULL;
	file = NULL;
	if ((tmp = ft_getenv(env, "HOME")) == NULL)
		tmp = ft_strdup("/tmp");
	file = ft_strjoindel(tmp, "/.alias");
	if (access(file, F_OK | R_OK) == 0)
	{
		fd = open(file, O_RDONLY);
		while (get_next_line(fd, &line) == 1)
		{
			if ((alias = new_node_alias(alias, line)) == NULL)
				return (NULL);
			ft_strdel(&line);
		}
		close(fd);
	}
	ft_strdel(&file);
	return (alias);
}

int					check_existing_alias(t_alias *alias, char *name)
{
	while (alias)
	{
		if (ft_strcmp(alias->name, name) == 0)
			return (0);
		alias = alias->next;
	}
	return (1);
}
