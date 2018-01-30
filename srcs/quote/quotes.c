/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:20:50 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:36:51 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

static char	*little_loop(char *line, char **new, char ***environ, t_hist *list)
{
	*new = ft_move(&list, environ);
	line = ft_realloc(line, ft_strlen(line),
			ft_strlen(line) + ft_strlen(*new) + 1);
	line = ft_strcat(line, "\n");
	line = ft_strcat(line, *new);
	return (line);
}

static char	*loop(char *line, char **new, char ***environ, t_hist *list)
{
	ft_strdel(new);
	ft_putcolor("> ", LIGHT_MAGENTA);
	ft_setenv("PROMPT", "2", environ);
	*new = ft_move(&list, environ);
	line = ft_realloc(line, ft_strlen(line),
			ft_strlen(line) + ft_strlen(*new) + 1);
	line = ft_strcat(line, "\n");
	line = ft_strcat(line, *new);
	ft_putchar('\n');
	return (line);
}

static char	*brackets(char *line, char c, char ***environ, t_hist *list)
{
	char	*new;

	new = NULL;
	if (c == '(')
	{
		while (new == NULL || ft_strchr(new, ')') == 0)
			line = loop(line, &new, environ, list);
	}
	else if (c == '[')
	{
		while (new == NULL || ft_strchr(new, ']') == 0)
			line = loop(line, &new, environ, list);
	}
	else if (c == '{')
	{
		while (new == NULL || ft_strchr(new, '}') == 0)
			line = loop(line, &new, environ, list);
	}
	ft_strdel(&new);
	return (line);
}

static char	*find_prompt(char c)
{
	char	*prompt;

	if (c == '\'')
		prompt = ft_strdup("quote> ");
	else if (c == '"')
		prompt = ft_strdup("dquote> ");
	else
		prompt = ft_strdup("> ");
	return (prompt);
}

char		*dquote(char *line, char c, char ***environ, t_hist *list)
{
	char	*new;
	char	*prompt;
	char	*tmp;

	new = NULL;
	prompt = NULL;
	if (c == '[' || c == '{' || c == '(')
		line = brackets(line, c, environ, list);
	else
	{
		while (new == NULL || ft_strchr(new, c) == 0)
		{
			ft_strdel(&prompt);
			prompt = find_prompt(c);
			ft_putcolor(prompt, LIGHT_MAGENTA);
			tmp = ft_itoa(ft_strlen(prompt));
			ft_setenv("PROMPT", tmp, environ);
			ft_strdel(&tmp);
			ft_strdel(&new);
			line = little_loop(line, &new, environ, list);
			ft_putchar('\n');
		}
		del_quotes(&new, &prompt);
	}
	return (line);
}
