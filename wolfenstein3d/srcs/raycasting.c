/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:20:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/02 19:45:12 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline int		fetch_color(t_wolf3d *w)
{
	return (w->colors[(w->map->board[w->cam->intersection.y / BLOC_SIZE]
									[w->cam->intersection.x / BLOC_SIZE]) % 3]);
}


static inline void		render(t_wolf3d *w, int i, int hit)
{
	int		h_seen;
	t_point	raytravel;
	double	depth;
	int		y;
	int		x;

	raytravel.y = w->cam->rays[i].endpoint.y - w->cam->position.y;
	raytravel.x = w->cam->rays[i].endpoint.x - w->cam->position.x;
	depth = raytravel.x * tcos(w->cam->angle)
											+ raytravel.y * tsin(w->cam->angle);
	h_seen = CAM_DIST * WALL_H / depth;
	y = CAM_H - (h_seen / 2) - 1;
	x = -1;
	while (++x < y + 151)
		put_pixel_img(w, w->width - i + w->mini_w, x, 0x09e4ef);
	if (hit == 1)
		while (++y < (CAM_H + (h_seen / 2)))
			put_pixel_img(w, w->width - i + w->mini_w, y + 150, fetch_color(w));
	while (++y < w->width)
		put_pixel_img(w, w->width - i + w->mini_w, y + 150, GREY);
}

static inline int		intersection_ver(t_wolf3d *w, t_vec2f *dir)
{
	t_point			a;
	int				hit;
	t_point			offset;

	hit = 0;
	if (dir->x < 0)
	{
		a.x = floor(w->cam->position.x / BLOC_SIZE) * BLOC_SIZE - 1;
		offset.x = -BLOC_SIZE;
	}
	else
	{
		a.x = floor(w->cam->position.x / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		offset.x = BLOC_SIZE;
	}
	a.y = w->cam->position.y + (w->cam->position.x - a.x) * dir->x / dir->y;
	offset.y = BLOC_SIZE * dir->x / dir->y;
	while (hit == 0 && a.x < w->mini_w && a.y < w->mini_h)
	{
		if (a.x / BLOC_SIZE >= 0 && a.y / BLOC_SIZE >= 0 &&
			w->map->board[(int)a.y / BLOC_SIZE][(int)a.x / BLOC_SIZE])
		{
			// printf("a.x = %d, a.y = %d\n", a.x, a.y);
			w->cam->intersection_ver.x = a.x;
			w->cam->intersection_ver.y = a.y;
			hit = 1;
		}
		a.x = a.x + offset.x;
		a.y = a.y + offset.y;
	}
	return (hit);
}

static inline int		intersection_hor(t_wolf3d *w, t_vec2f *dir)
{
	t_point			a;
	int				hit;
	t_point			offset;

	hit = 0;
	if (dir->y > 0)
	{
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE - 1;
		offset.y = -BLOC_SIZE;
	}
	else
	{
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		offset.y = BLOC_SIZE;
	}
	a.x = w->cam->position.x + (w->cam->position.y - a.y) * dir->y / dir->x;
	offset.x = BLOC_SIZE * dir->y / dir->x;
	while (hit == 0 && a.x < w->mini_w && a.y < w->mini_h)
	{
		if (a.x / BLOC_SIZE >= 0 && a.y / BLOC_SIZE >= 0 &&
			w->map->board[(int)a.y / BLOC_SIZE][(int)a.x / BLOC_SIZE])
		{
			// printf("a.x = %d, a.y = %d\n", a.x, a.y);
			w->cam->intersection_hor.x = a.x;
			w->cam->intersection_hor.y = a.y;
			hit = 1;
		}
		a.x += offset.x;
		a.y += offset.y;
	}
	return (hit);
}
void					raycasting(t_wolf3d *w, int limit)
{
	int			i;
	int			hit;
	t_vec2f		dir;
	t_vec2f		forward;
	t_vec2f		right;
	double		halfwidth;
	double		offset;

	i = -1;
	//printf("angle: %f\n", w->cam->angle);
	forward.x = tcos(w->cam->angle);
	forward.y = tsin(w->cam->angle);
	right.x = forward.y;
	right.y = -forward.x;
	halfwidth = ttan(w->cam->fov / 2.0);
	while (++i < limit && !(hit = 0))
	{
		w->cam->rays[i].startpoint = w->cam->position;
		w->cam->rays[i].startpoint.color = 0xff0000;
		offset = ((i * 2.0 / (limit - 1.0)) - 1.0) * halfwidth;
		dir.x = forward.x + offset * right.x;
		dir.y = forward.y + offset * right.y;
		if ((hit = intersection(w, &dir)))
			w->cam->rays[i].endpoint = w->cam->intersection;
		else
		{
			w->cam->rays[i].endpoint.x = w->cam->position.x + w->cam->raylength
				* dir.x;
			w->cam->rays[i].endpoint.y = w->cam->position.y + w->cam->raylength
				* dir.y;
		}
		limit == w->width ? render(w, i, hit) : 0;
	}
}
