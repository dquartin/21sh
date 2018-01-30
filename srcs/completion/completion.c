/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 10:40:23 by hlely             #+#    #+#             */
/*   Updated: 2018/01/30 09:58:46 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int		first_word(char **stock, int i)
{
	if (ft_strchr(stock[i], '/'))
		return (0);
	if (i != 0)
	{
		if (!ft_strcmp(stock[i - 1], ";") && !ft_strcmp(stock[i - 1], "|"))
			return (1);
		else
			return (0);
	}
	return (1);
}

void	completion_sd_line(char *tmp, char **stock,
		t_index **index, t_list **entry)
{
	char	*path;

	if ((tmp = ft_strrchr(stock[env_len(stock) - 1], '/')) == NULL)
		*entry = get_entry(".");
	else
	{
		path = ft_strsub(stock[env_len(stock) - 1], 0,
				ft_strlen(stock[env_len(stock) - 1]) - ft_strlen(tmp));
		if (opendir(path) == NULL)
		{
			(*index)->list = NULL;
			ft_strdel(&path);
			return ;
		}
		*entry = get_entry(path);
		ft_strdel(&path);
	}
	(*index)->list = get_matching_entry(stock[env_len(stock) - 1], *entry);
}

void	completion(t_index **index)
{
	char	*tmp;
	char	**stock;
	t_list	*entry;

	stock = NULL;
	entry = NULL;
	stock = ft_splitwhite((*index)->line);
	tmp = stock[env_len(stock) - 1];
	if ((*index)->i > 1 && tmp[0] == '.' && tmp[1] == '/')
		(*index)->list = get_executable(tmp);
	else if (first_word(stock, env_len(stock) - 1)
			&& (*index)->line[(*index)->i - 1] == ' ')
		(*index)->list = get_entry(".");
	else if (first_word(stock, env_len(stock) - 1)
			&& (*index)->i > 0 && (*index)->line[(*index)->i] != ' ')
	{
		entry = get_bin_entry();
		(*index)->list = get_matching_entry(stock[env_len(stock) - 1], entry);
	}
	else if (stock)
		completion_sd_line(tmp, stock, index, &entry);
	ft_lst_clear(&entry);
	delete_lines(&stock);
	stock ? free(stock) : 0;
	(*index)->start = (*index)->list;
}
