/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoindel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 11:18:34 by dquartin          #+#    #+#             */
/*   Updated: 2017/12/04 11:24:54 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoindel(char *s1, const char *s2)
{
	char	*new;

	new = ft_strnew((int)(ft_strlen(s1) + ft_strlen((char*)s2)) + 1);
	new = ft_strcat(new, s1);
	free(s1);
	new = ft_strcat(new, s2);
	new[(int)(ft_strlen(s1) + ft_strlen(s2) + 1)] = '\0';
	return (new);
}

char	*ft_strjoindeldel(char *s1, char *s2)
{
	char	*new;

	new = ft_strnew((int)(ft_strlen(s1) + ft_strlen(s2)) + 1);
	new = ft_strcat(new, s1);
	free(s1);
	new = ft_strcat(new, s2);
	free(s2);
	return (new);
}
