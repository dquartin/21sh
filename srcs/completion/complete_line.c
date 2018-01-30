/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 12:28:27 by hlely             #+#    #+#             */
/*   Updated: 2018/01/29 17:12:11 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	complete_line(t_index **index)
{
	if ((*index)->i && (*index)->start)
	{
		while ((*index)->i > 0 && (*index)->line[(*index)->i - 1]
				!= ' ' && (*index)->line[(*index)->i - 1] != '/')
			begin(index);
		ft_putstrin((*index)->list->content);
		(*index)->i += ft_strlen((*index)->list->content);
		(*index)->x += ft_strlen((*index)->list->content);
		(*index)->line = ft_strjoindel((*index)->line, (*index)->list->content);
		if ((*index)->list->next)
			(*index)->list = (*index)->list->next;
		else
			(*index)->list = (*index)->start;
	}
}
