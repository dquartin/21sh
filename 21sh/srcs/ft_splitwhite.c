/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitwhite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:00:38 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/13 10:25:25 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		count_words(const char *s)
{
	int		i;
	int		words;

	i = 0;
	if (s[0] == ' ' || s[0] == '\t')
		words = 0;
	else
		words = 1;
	while (s[i])
	{
		if (s[i] && (s[i] == ' ' || s[i] == '\t') && s[i + 1] != ' ' &&
				s[i + 1] != '\t' && s[1 + i] != '\0')
			words++;
		i++;
	}
	return (words);
}

static void		substitute_loop(char const *s, char **semitab)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (j < count_words(s))
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		start = i;
		while (s[i] && s[i] != ' ' && s[i] != '\t')
			i++;
		semitab[j] = ft_strsub(s, (unsigned int)start, (size_t)(i - start));
		j++;
	}
	semitab[j] = 0;
}

char			**ft_splitwhite(char const *s)
{
	char	**semitab;

	if (!s)
		return (0);
	if (s[0] == '\0')
	{
		if (!(semitab = (char**)malloc(sizeof(char*))))
			return (0);
		semitab[0] = 0;
		return (semitab);
	}
	if (!(semitab = (char**)malloc(sizeof(char*) * ((count_words(s) + 1)))))
		return (0);
	substitute_loop(s, semitab);
	return (semitab);
}
