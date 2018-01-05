/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 17:27:00 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/08 14:38:48 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_cmptwrds(char const *s, char c)
{
	int		cpt_wrds;
	int		i;

	i = 0;
	cpt_wrds = 1;
	if (s[0] == c)
		cpt_wrds = 0;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			cpt_wrds++;
		i++;
	}
	return (cpt_wrds);
}

static char		**ft_intermed(char const *s, char c, char **new)
{
	int		i;
	int		j;
	int		start;
	int		len;

	i = 0;
	j = 0;
	while (j < ft_cmptwrds(s, c))
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		len = i;
		new[j] = ft_strsub(s, (unsigned int)start, (size_t)(len - start));
		j++;
	}
	new[j] = 0;
	return (new);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**new;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
	{
		if (!(new = (char**)malloc(sizeof(char*))))
			return (NULL);
		new[0] = 0;
		return (new);
	}
	if (!(new = (char**)malloc(sizeof(char*) * (ft_cmptwrds(s, c) + 1))))
		return (NULL);
	new = ft_intermed(s, c, new);
	return (new);
}
