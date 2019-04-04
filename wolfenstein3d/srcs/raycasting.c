/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:20:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/04 21:41:00 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// static inline int		fetch_color(t_wolf3d *w)
// {
// 	return (w->colors[(w->map->board[(int)w->cam->intersection.y / BLOC_SIZE]
// 									[(int)w->cam->intersection.x / BLOC_SIZE]) % 3]);
// }


static inline void		render(t_wolf3d *w, int i, double depth)
{
	int		h_seen;
	int		y;
	int		x;

	h_seen = CAM_DIST * WALL_H / depth;
	y = CAM_H - (h_seen / 2) - 1;
	x = -1;
	// while (++x < y + 151)
	// 	put_pixel_img(w, w->width - i + w->mini_w, x, 0x09e4ef);
	while (++y < (CAM_H + (h_seen / 2)))
		put_pixel_img(w, w->width - i + w->mini_w, y + 150, 0xff0000);
	// while (++y < w->width)
	// 	put_pixel_img(w, w->width - i + w->mini_w, y + 150, GREY);
}

static inline void 		inter_hor(t_wolf3d *w, int i, t_vec2f *dir)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset

	if (dir->y < 0) // ray is facing up
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE - 1;
	else
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
	a.x = w->cam->position.x + (w->cam->position.y - a.y) / dir->y / dir->x;
	o.x = BLOC_SIZE / dir->y / dir->x;
	while (a.x >= 0 && a.y >= 0 && a.x < w->mini_w && a.y < w->mini_h)
	{
		if (w->map->board[(int)a.y / BLOC_SIZE][(int)a.x / BLOC_SIZE])
		{
			w->cam->inter[i][0] = (t_vec2f){.x = a.x, .y = a.y};
			break;
		}
		a.x += (dir->x < 0) ? -o.x : o.x;
		a.y += (dir->y < 0) ? -BLOC_SIZE : BLOC_SIZE;
	}
}

static inline void 		inter_ver(t_wolf3d *w, int i, t_vec2f *dir)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset

	if (dir->x < 0) // ray is facing left
		a.x = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE - 1;
	else
		a.x = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
	a.y = w->cam->position.y + (w->cam->position.x - a.x) * dir->y / dir->x;
	o.y = BLOC_SIZE * dir->y / dir->x;
	while (a.x >= 0 && a.y >= 0 && a.x < w->mini_w && a.y < w->mini_h)
	{
		if (w->map->board[(int)a.y / BLOC_SIZE][(int)a.x / BLOC_SIZE])
		{
			w->cam->inter[i][1] = (t_vec2f){.x = a.x, .y = a.y};
			break;
		}
		a.x += (dir->x < 0) ? -BLOC_SIZE : BLOC_SIZE;
		a.y += (dir->y < 0) ? -o.y : o.y;
	}
}

double					get_distowall(t_wolf3d *w, int i)
{
	//t_vec2f		raytravel;
	double		dist_hor;
	double		dist_ver;

	// raytravel.x = w->cam->inter[i][0].x - w->cam->position.x;
	// raytravel.y = w->cam->inter[i][0].y - w->cam->position.y;
	dist_hor = sqrt(pow((w->cam->inter[i][0].x - w->cam->position.x), 2) + pow(
		(w->cam->inter[i][0].y - w->cam->position.y), 2));
	dist_ver = sqrt(pow((w->cam->inter[i][1].x - w->cam->position.x), 2) + pow(
		(w->cam->inter[i][1].y - w->cam->position.y), 2));
	printf("d_ver = %f, d_hor = %f\n", dist_ver, dist_hor);
	if (dist_hor && dist_ver && dist_hor < dist_ver)
	{
		w->cam->rays[i] = w->cam->inter[i][0];
		return (dist_hor);
	}
	if (dist_hor && dist_ver && dist_ver < dist_ver)
	{
		w->cam->rays[i] = w->cam->inter[i][1];
		return (dist_ver);
	}
	return (0);
}
void					raycasting(t_wolf3d *w, int limit)
{
	int			i;
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
	while (++i < limit)
	{
		w->cam->rays[i].color = 0xff0000;
		offset = ((i * 2.0 / (limit - 1.0)) - 1.0) * halfwidth;
		dir.x = forward.x + offset * right.x;
		dir.y = forward.y + offset * right.y;
		inter_hor(w, i, &dir);
		inter_ver(w, i, &dir);
		limit == w->width ? render(w, i, get_distowall(w, i)) : 0;
	}
}
