/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:03:54 by dquartin          #+#    #+#             */
/*   Updated: 2017/11/08 19:00:55 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*new;
	int		i;
	int		start;
	int		len;

	i = 0;
	start = 0;
	len = 0;
	if (!s)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	start = i;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
			len = i;
		i++;
	}
	if (len == 0 && start > 0)
		return (ft_strdup("\0"));
	if (!(new = ft_strsub(s, (unsigned int)start, (size_t)(len - start + 1))))
		return (NULL);
	return (new);
}
