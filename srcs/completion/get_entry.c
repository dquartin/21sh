/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:12:34 by hlely             #+#    #+#             */
/*   Updated: 2018/01/30 10:41:30 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

t_list	*get_bin_entry(void)
{
	DIR				*dir;
	struct dirent	*info;
	t_list			*tmp;
	t_list			*list;

	list = NULL;
	if ((dir = opendir("/bin")) == NULL)
		ft_putstr("ERROR");
	while ((info = readdir(dir)))
	{
		tmp = ft_lstnew(info->d_name, ft_strlen(info->d_name) + 1);
		ft_lst_add_end(&list, tmp);
	}
	closedir(dir);
	dir = opendir("/usr/bin");
	while ((info = readdir(dir)))
	{
		tmp = ft_lstnew(info->d_name, ft_strlen(info->d_name) + 1);
		ft_lst_add_end(&list, tmp);
	}
	closedir(dir);
	return (list);
}

t_list	*get_entry(char *path)
{
	DIR				*dir;
	struct dirent	*info;
	t_list			*tmp;
	t_list			*list;

	list = NULL;
	dir = opendir(path);
	while ((info = readdir(dir)))
	{
		if (info->d_name[0] != '.')
		{
			tmp = ft_lstnew(info->d_name, ft_strlen(info->d_name) + 1);
			ft_lst_add_end(&list, tmp);
		}
	}
	closedir(dir);
	return (list);
}

t_list	*get_executable_v2(char *path)
{
	DIR				*dir;
	t_list			*list;
	t_list			*tmp;
	struct dirent	*info;

	dir = opendir(path);
	while ((info = readdir(dir)))
	{
		if (info->d_name[0] != '.' && !access(info->d_name, F_OK | X_OK))
		{
			tmp = ft_lstnew(info->d_name, ft_strlen(info->d_name) + 1);
			ft_lst_add_end(&list, tmp);
		}
	}
	closedir(dir);
	return (list);
}

t_list	*get_executable(char *path)
{
	char			*path_tmp;
	t_list			*list;

	list = NULL;
	if (ft_strcmp(path, "./"))
	{
		path = ft_strchr(path, '/');
		path_tmp = ft_strjoin(".", path);
		list = get_entry(path_tmp);
		ft_strdel(&path_tmp);
	}
	else
		list = get_executable_v2(path);
	return (list);
}

t_list	*get_matching_entry(char *path, t_list *entry)
{
	char	*to_find;
	t_list	*matching;
	t_list	*tmp;

	matching = NULL;
	to_find = ft_strrchr(path, '/') ?
		ft_strrchr(path, '/') + 1 : path;
	while (entry)
	{
		if (!ft_strncmp(entry->content, to_find, ft_strlen(to_find)))
		{
			tmp = ft_lstnew(entry->content, entry->content_size + 1);
			ft_lst_add_end(&matching, tmp);
		}
		entry = entry->next;
	}
	return (matching);
}
