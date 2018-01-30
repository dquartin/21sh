/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 20:31:31 by dquartin          #+#    #+#             */
/*   Updated: 2018/01/29 14:33:07 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	ft_lstaddnew(t_hist **alst, t_hist *new)
{
	new->next = *alst;
	new->prev = NULL;
	if (*alst)
		(new->next)->prev = new;
	*alst = new;
}

t_hist	*ft_lstcreate(void const *content)
{
	t_hist	*new;

	if (!(new = (t_hist*)malloc(sizeof(t_hist))))
		return (NULL);
	if (!content)
		new->histo = NULL;
	else
		new->histo = ft_strdup(content);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
