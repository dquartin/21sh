/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlely <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 17:49:04 by hlely             #+#    #+#             */
/*   Updated: 2018/02/28 16:01:26 by dquartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void	exit_atty(void)
{
	ERROR("Error : not a valid terminal. Exiting...");
	exit(EXIT_FAILURE);
}