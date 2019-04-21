/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:18:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/21 19:40:45 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static double	toradian(double angle)
{
	return (angle * M_PI / 180.0);
}

double			tcos(double angle)
{
	return (cos(toradian(angle)));
}

double			tsin(double angle)
{
	return (sin(toradian(angle)));
}

double			ttan(double angle)
{
	return (tan(toradian(angle)));
}

void			end(char *str, int fd)
{
	ft_putendl_fd(str, 2);
	close(fd);
	exit(1);
}
