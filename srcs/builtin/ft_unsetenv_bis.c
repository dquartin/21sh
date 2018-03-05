/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dquartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:04:30 by dquartin          #+#    #+#             */
/*   Updated: 2018/02/28 15:14:16 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	error_unsetenv(void)
{
	ft_putstrerror("Error: Unsetenv function takes a name");
	ERROR(" as argument.");
	g_status = 0;
}
