/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:20:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/22 18:54:57 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	inline	void		inter_hor(t_wolf3d *w, int i, double angle)
{
	t_vec2f	a;
	t_vec2f	o;
	double	tangent;

	tangent = w->tan_table[i] + 0.001;
	a.y = (angle <= 180) ? floor(w->cam->position.y / 64) *
	64 - 1 : floor(w->cam->position.y / 64) * 64 + 64;
	o.y = (angle < 180) ? -64 : 64;
	o.x = (angle < 90 || angle > 270) ? 64 / tangent : -64 / tangent;
	a.x = (angle < 359.95) ? w->cam->position.x + (w->cam->position.y - a.y) /
	tangent : w->cam->position.x + (w->cam->position.y - a.y) / -tangent;
	a.x = (angle >= 179.95 && angle <= 180) ? w->cam->position.x +
	(w->cam->position.y - a.y) / -tangent : a.x;
	if ((angle > 90 && angle <= 270 && (int)ceil(a.x) / 64 >= w->map->w) ||
		a.x < 0 || a.x >= w->mini_w)
		a.x = (a.x < 0) ? 0 : w->mini_w - 64;
	while ((angle > 90 && angle <= 270 && w->map->board[(int)a.y / 64]
		[(int)ceil(a.x) / 64] == 0)
		|| ((angle > 270 || angle <= 90) && w->map->board[(int)a.y / 64]
			[(int)a.x / 64] == 0))
	{
		a.x += ((angle >= 90 && angle < 180) || angle >= 270) ? -o.x : o.x;
		a.y += o.y;
		if ((angle > 90 && angle <= 270 && (int)ceil(a.x) / 64 >= w->map->w) ||
			a.x < 0 || a.x >= w->mini_w)
			a.x = (a.x < 0) ? 0 : w->mini_w - 64;
		if (a.y < 0 || a.y >= w->mini_h)
			break;
	}
	w->cam->interh[i].x = a.x;
	w->cam->interh[i].y = a.y;
}

static inline void 		inter_ver(t_wolf3d *w, int i, double angle)
{
	t_vec2f	a;
	t_vec2f	o;
	double	tangent;

	tangent = w->tan_table[i] + 0.001;
	a.x = (angle >= 90 && angle < 270) ? floor(w->cam->position.x / 64) *
	64 - 1 : floor(w->cam->position.x / 64) * 64 + 64;
	o.x = (angle > 90 && angle < 270) ? -64 : 64;
	o.y = (angle > 0 &&  angle < 180) ? -64 * tangent : 64 * tangent;
	a.y = (angle != 270 && angle != 90) ? w->cam->position.y + (w->cam->position.x
		- a.x) * tangent : w->cam->position.y + (w->cam->position.x - a.x) * -tangent;
	if ((angle < 180 && (int)ceil(a.y) / 64 > w->map->h) || a.y < 0 ||
		a.y >= w->mini_h)
		a.y = (a.y < 0) ? 0 : w->mini_h - 64;
	while ((angle < 180 && w->map->board[(int)ceil(a.y) / 64][(int)ceil(a.x) / 64] == 0)
		|| (angle >= 180 && w->map->board[(int)a.y / 64][(int)ceil(a.x) / 64] == 0))
	{
		a.y += ((angle > 90 && angle < 180) || angle > 270) ? -o.y : o.y;
		a.x += o.x;
		if ((angle < 180 && (int)ceil(a.y) / 64 > w->map->h) || a.y < 0 || a.y >=
			w->mini_h)
			a.y = (a.y < 0) ? 0 : w->mini_h - 64;
		if ((int)ceil(a.x) / 64 > w->map->w || a.x < 0 || a.x > w->mini_w - 1)
			break;
	}
	w->cam->interv[i].x = a.x;
	w->cam->interv[i].y = a.y;
}

void					check_direction(t_wolf3d *w, int i, t_thread_data *d)
{
	if (!d->inter)
	{
		if (w->cam->rays[i].y - w->cam->position.y >= 0)
			d->direction = NORTH;
		else
			d->direction = SOUTH;
	}
	else
	{
		if (w->cam->rays[i].x - w->cam->position.x >= 0)
			d->direction = WEST;
		else
			d->direction = EAST;
	}

}

double					get_distowall(t_wolf3d *w, int i, t_thread_data *d)
{
	double		dist_hor;
	double		dist_ver;

	dist_hor = sqrt(pow((w->cam->interh[i].x - w->cam->position.x), 2) + pow(
		(w->cam->interh[i].y - w->cam->position.y), 2));
	dist_ver = sqrt(pow((w->cam->interv[i].x - w->cam->position.x), 2) + pow(
		(w->cam->interv[i].y - w->cam->position.y), 2));
	if (dist_hor < dist_ver)
	{
		w->cam->rays[i] = w->cam->interh[i];
		d->inter = 0;
		check_direction(w, i, d);
	}
	else
	{
		w->cam->rays[i] = w->cam->interv[i];
		d->inter = 1;
		check_direction(w, i, d);
	}
	return ((dist_hor > dist_ver) ? dist_ver : dist_hor);
}

void					*raycasting(void *data)
{
	int				i;
	double			angle;
	double 			dist;
	t_thread_data	*d;
	t_wolf3d		*w;

	d = (t_thread_data *)data;
	w = d->w;
	i = d->x;
	cos_lookuptable(w, d);
	tan_lookuptable(w, d);
	while (i < d->x_end)
	{
		w->cam->rays[i].color = RED;
		angle = w->cam->angle + w->cam->fov / 2 - (i * w->cam->fov / w->width);
		(angle < 0) && (angle += 360);
		(angle > 360) && (angle -= 360);
		inter_ver(w, i, angle);
		inter_hor(w, i, angle);
		dist = get_distowall(w, i, d);
		render(w, i, dist, d);
		i++;
	}
	return (0);
}
