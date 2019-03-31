/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:18:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/31 15:37:44 by midrissi         ###   ########.fr       */
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
