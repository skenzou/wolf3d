/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:18:44 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/31 14:35:55 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static float	toradian(float angle)
{
	return (angle * M_PI / 180.0);
}

float			tcos(float angle)
{
	return (cos(toradian(angle)));
}

float			tsin(float angle)
{
	return (sin(toradian(angle)));
}

float			ttan(float angle)
{
	return (tan(toradian(angle)));
}
