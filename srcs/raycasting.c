/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:20:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/23 14:21:23 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void			check_direction(t_thread_data *d)
{
	if (!d->inter)
	{
		if (d->w->cam->rays[d->i].y - d->w->cam->position.y >= 0)
			d->direction = NORTH;
		else
			d->direction = SOUTH;
	}
	else
	{
		if (d->w->cam->rays[d->i].x - d->w->cam->position.x >= 0)
			d->direction = WEST;
		else
			d->direction = EAST;
	}
}

static inline double		get_distowall(t_thread_data *d)
{
	double		dist_hor;
	double		dist_ver;

	dist_hor = sqrt(pow((d->w->cam->interh[d->i].x - d->w->cam->position.x), 2)
				+ pow((d->w->cam->interh[d->i].y - d->w->cam->position.y), 2));
	dist_ver = sqrt(pow((d->w->cam->interv[d->i].x - d->w->cam->position.x), 2)
				+ pow((d->w->cam->interv[d->i].y - d->w->cam->position.y), 2));
	if (dist_hor < dist_ver)
	{
		d->w->cam->rays[d->i] = d->w->cam->interh[d->i];
		d->inter = 0;
		check_direction(d);
	}
	else
	{
		d->w->cam->rays[d->i] = d->w->cam->interv[d->i];
		d->inter = 1;
		check_direction(d);
	}
	return ((dist_hor > dist_ver) ? dist_ver : dist_hor);
}

void						*raycasting(void *data)
{
	double			angle;
	double			dist;
	t_thread_data	*d;
	t_wolf3d		*w;

	d = (t_thread_data *)data;
	w = d->w;
	d->i = d->x;
	cos_lookuptable(w, d);
	tan_lookuptable(w, d);
	while (d->i < d->x_end)
	{
		w->cam->rays[d->i].color = RED;
		angle = w->cam->angle + w->cam->fov / 2 -
												(d->i * w->cam->fov / w->width);
		(angle < 0) && (angle += 360);
		(angle > 360) && (angle -= 360);
		inter_ver(d, angle);
		inter_hor(d, angle);
		dist = get_distowall(d);
		render(dist, d, angle);
		d->i++;
	}
	return (0);
}
