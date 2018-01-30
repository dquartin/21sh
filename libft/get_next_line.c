/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:44:13 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/24 11:59:11 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*fill(int res, int fd, char *buffer, char *stock)
{
	int		i;

	i = 0;
	while (res == BUFF_SIZE)
	{
		if (i >= BUFF_SIZE)
		{
			ft_bzero(buffer, BUFF_SIZE);
			res = read(fd, buffer, BUFF_SIZE);
			stock = ft_realloc(stock, (int)ft_strlen(stock),
					(int)(ft_strlen(stock) + BUFF_SIZE));
			i = 0;
		}
		while (i < BUFF_SIZE)
		{
			stock = ft_strncat(stock, buffer + i, 1);
			i++;
		}
		if (fd == 0 && buffer[res - 1] == '\n')
		{
			stock[ft_strlen(stock) - 1] = '\0';
			return (stock);
		}
	}
	return (stock);
}

char	*first(const int fd, char *stock)
{
	int		res;
	char	buffer[BUFF_SIZE];

	ft_bzero(buffer, BUFF_SIZE);
	res = read(fd, buffer, BUFF_SIZE);
	if (fd < 0 || res < 0 || BUFF_SIZE <= 0)
		return (0);
	stock = ft_strnew(BUFF_SIZE);
	if (res < BUFF_SIZE)
	{
		stock = ft_strcpy(stock, buffer);
		stock[res] = '\0';
		if (fd == 0 && buffer[res - 1] == '\n')
			stock[res - 1] = '\0';
	}
	stock = fill(res, fd, buffer, stock);
	ft_bzero(buffer, BUFF_SIZE);
	return (stock);
}

char	*get_line(char *stock, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (stock[i] != '\n')
	{
		*line = ft_strncat(*line, stock + i, 1);
		i++;
	}
	tmp = ft_strdup(stock);
	ft_strdel(&stock);
	stock = ft_strdup(ft_strchr(tmp, '\n') + 1);
	ft_strdel(&tmp);
	return (stock);
}

int		get_next_line(const int fd, char **line)
{
	static char		*stock = NULL;

	if (stock == NULL)
		if ((stock = first(fd, stock)) == 0)
			return (-1);
	if (stock != NULL)
	{
		if (stock[0] == '\0')
		{
			ft_strdel(&stock);
			return (0);
		}
		*line = ft_strnew(ft_strlen(stock));
		if (ft_strchr(stock, '\n') == NULL)
		{
			*line = ft_strcat(*line, stock);
			stock[0] = '\0';
			if (fd == 0)
				ft_strdel(&stock);
			return (1);
		}
		stock = get_line(stock, line);
	}
	return (1);
}
