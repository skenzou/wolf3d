/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:49:38 by rkamegne          #+#    #+#             */
/*   Updated: 2019/04/23 15:08:01 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void			init_hor(t_thread_data *d,
										double angle, t_vec2f *a, t_vec2f *o)
{
	double	tangent;

	tangent = d->w->tan_table[d->i] + 0.001;
	a->y = (angle <= 180) ? floor(d->w->cam->position.y / 64) *
	64 - 1 : floor(d->w->cam->position.y / 64) * 64 + 64;
	o->y = (angle < 180) ? -64 : 64;
	o->x = (angle < 90 || angle > 270) ? 64 / tangent : -64 / tangent;
	a->x = (angle < 359.95) ? d->w->cam->position.x +
	(d->w->cam->position.y - a->y) / tangent
	: d->w->cam->position.x + (d->w->cam->position.y - a->y) / -tangent;
	a->x = (angle >= 179.95 && angle <= 180) ? d->w->cam->position.x +
	(d->w->cam->position.y - a->y) / -tangent : a->x;
}

void						inter_hor(t_thread_data *d, double angle)
{
	t_vec2f	a;
	t_vec2f	o;

	init_hor(d, angle, &a, &o);
	if ((angle > 90 && angle <= 270 && (int)ceil(a.x) / 64 >= d->w->map->w) ||
		a.x < 0 || a.x >= d->w->mini_w)
		a.x = (a.x < 0) ? 0 : d->w->mini_w - 64;
	while ((angle > 90 && angle <= 270 && d->w->map->board[(int)a.y / 64]
		[(int)ceil(a.x) / 64] == 0)
		|| ((angle > 270 || angle <= 90) && d->w->map->board[(int)a.y / 64]
			[(int)a.x / 64] == 0))
	{
		a.x += ((angle >= 90 && angle < 180) || angle >= 270) ? -o.x : o.x;
		a.y += o.y;
		if ((angle > 90 && angle <= 270 && (int)ceil(a.x) / 64 >= d->w->map->w)
			|| a.x < 0 || a.x >= d->w->mini_w)
			a.x = (a.x < 0) ? 0 : d->w->mini_w - 64;
		if (a.y < 0 || a.y >= d->w->mini_h)
			break ;
	}
	d->w->cam->interh[d->i].x = a.x;
	d->w->cam->interh[d->i].y = a.y;
}

static inline void			init_ver(t_thread_data *d,
										double angle, t_vec2f *a, t_vec2f *o)
{
	double	tangent;

	tangent = d->w->tan_table[d->i] + 0.001;
	a->x = (angle >= 90 && angle < 270) ? floor(d->w->cam->position.x / 64) *
	64 - 1 : floor(d->w->cam->position.x / 64) * 64 + 64;
	o->x = (angle > 90 && angle < 270) ? -64 : 64;
	o->y = (angle > 0 && angle < 180) ? -64 * tangent : 64 * tangent;
	a->y = (angle != 270 && angle != 90) ? d->w->cam->position.y +
	(d->w->cam->position.x - a->x) * tangent
	: d->w->cam->position.y + (d->w->cam->position.x - a->x) * -tangent;
}

void						inter_ver(t_thread_data *d, double angle)
{
	t_vec2f	a;
	t_vec2f	o;

	init_ver(d, angle, &a, &o);
	if ((angle < 180 && (int)ceil(a.y) / 64 > d->w->map->h) || a.y < 0 ||
		a.y >= d->w->mini_h)
		a.y = (a.y < 0) ? 0 : d->w->mini_h - 64;
	while ((angle < 180 && d->w->map->board[(int)ceil(a.y) / 64]
		[(int)ceil(a.x) / 64] == 0) || (angle >= 180 &&
				d->w->map->board[(int)a.y / 64][(int)ceil(a.x) / 64] == 0))
	{
		a.y += ((angle > 90 && angle < 180) || angle > 270) ? -o.y : o.y;
		a.x += o.x;
		if ((angle < 180 && (int)ceil(a.y) / 64 > d->w->map->h)
			|| a.y < 0 || a.y >= d->w->mini_h)
			a.y = (a.y < 0) ? 0 : d->w->mini_h - 64;
		if ((int)ceil(a.x) / 64 > d->w->map->w || a.x < 0
													|| a.x > d->w->mini_w - 1)
			break ;
	}
	d->w->cam->interv[d->i].x = a.x;
	d->w->cam->interv[d->i].y = a.y;
}
