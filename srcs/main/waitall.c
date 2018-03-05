/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdagnaud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:11:37 by rdagnaud          #+#    #+#             */
/*   Updated: 2018/02/15 14:19:05 by rdagnaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	waitall(int nbproc)
{
	int		i;

	while (nbproc > 0)
	{
		waitpid(WAIT_ANY, &i, 0);
		handle_segv(i);
		if (i != 0)
			g_status = 0;
		nbproc--;
	}
}
