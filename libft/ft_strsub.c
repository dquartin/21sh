/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:01:38 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/20 13:57:29 by hlely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	char			*new;

	i = start;
	j = 0;
	if (!s)
		return (0);
	if (!(new = ft_strnew(len)))
		return (NULL);
	while (j < len && s[i] && (new != NULL))
	{
		new[j] = s[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*ft_strsubdel(char *s, int start, size_t len)
{
	int		i;
	size_t	j;
	char	*new;

	i = start;
	j = 0;
	if (!s)
		return (0);
	new = ft_strnew(len);
	while (j < len && s[i] && (new != NULL))
	{
		new[j] = s[i];
		j++;
		i++;
	}
	new[j] = '\0';
	free(s);
	return (new);
}
