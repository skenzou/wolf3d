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
		put_pixel_img(w, /*w->width*/ i + w->mini_w, y + 150, 0xff0000);
	// while (++y < w->width)
	// 	put_pixel_img(w, w->width - i + w->mini_w, y + 150, GREY);
}

static inline void 		inter_hor(t_wolf3d *w, int i, double angle)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	double	tangent;

	tangent = ttan(angle) + 0.001;
	a.y = (angle <= 180) ? w->cam->position.y / 32 *
	32 - 1 : w->cam->position.y / 32 * 32 + 32;
	o.y = (angle < 180) ? -32 : 32;
	o.x = (angle < 90 || angle > 270) ? 32 / tangent : -32 / tangent;
	a.x = (angle != 180.0 && angle < 359.97) ? w->cam->position.x + (w->cam->position.y - a.y) / tangent :
	w->cam->position.x + (w->cam->position.y - a.y) / -tangent;
	a.x = (angle >= 179.97 && angle <= 180) ? w->cam->position.x + (w->cam->position.y - a.y) / -tangent : a.x;
	if (a.x < 0 || a.x >= w->mini_w - 1)
		a.x = (a.x < 0) ? 0 : w->mini_w - 1;
	printf("START ---HOR----Point of intersections : x = %f, y = %f o.x = %f, o.y = %f\n", ceil(a.x), a.y, o.x, o.y);
	while (w->map->board[(int)a.y / 32][(int)a.x / 32] == 0)
	{
		a.x += ((angle >= 90 && angle < 180) || angle >= 270) ? -o.x : o.x; 
		a.y += o.y;
		//printf("----INSIDE HOR----Point of intersections : x = %f, y = %f o.x = %f, o.y = %f\n", a.x, a.y, o.x, o.y);
		if (a.x < 0 || a.x >=  w->mini_w)
			a.x = (a.x < 0) ? 0 : w->mini_w - 1;
		if (a.y < 0 || a.y > w->mini_h - 1)
			break;
		//if (w->map->board[(int)a.y / 32][(int)a.x / 32] == 0)
			//printf("HIT\n");
	}
	w->cam->interh[i].x = a.x;
	w->cam->interh[i].y = a.y;
	printf("END ---HOR----Point of intersections : x = %f, y = %f o.x = %f, o.y = %f\n", a.x, a.y, o.x, o.y);
}

static inline void 		inter_ver(t_wolf3d *w, int i, double angle)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	double	tangent;

	tangent = ttan(angle) + 0.001;
	a.x = (angle >= 90 && angle < 270) ? w->cam->position.x / 32 *
	32 - 1 : w->cam->position.x / 32 * 32 + 32;
	o.x = (angle > 90 && angle < 270) ? -32 : 32;
	o.y = (angle > 0 &&  angle < 180) ? -32 * tangent : 32 * tangent;
	a.y = (angle != 270 && angle != 90) ? w->cam->position.y + (w->cam->position.x - a.x) * tangent :
	w->cam->position.y + (w->cam->position.x - a.x) * -tangent;
	if (a.y < 0 || a.y >=  w->mini_h)
		a.y = (a.y < 0) ? 0 : w->mini_h - 1;
	//printf("---VER----Point of intersections : x = %f, y = %f o.x = %f, o.y = %f\n", a.x, a.y, o.x, o.y);
	while (w->map->board[(int)a.y / 32][(int)a.x / 32] == 0)
	{
		a.y += ((angle > 90 && angle < 180) || angle > 270) ? -o.y : o.y;
		a.x += o.x;
		//printf("----INSIDE VER----Point of intersections : x = %f, y = %f o.x = %f, o.y = %f\n", a.x, a.y, o.x, o.y);
		if (a.y < 0 || a.y >=  w->mini_h)
			a.y = (a.y < 0) ? 0 : w->mini_h - 1;
		if (a.x < 0 || a.x > w->mini_w - 1)
			break;
		//if (w->map->board[(int)a.y / 32][(int)a.x / 32] == 0)
		//	printf("HIT\n");
	}
	w->cam->interv[i].x = a.x;
	w->cam->interv[i].y = a.y;
}

double					get_distowall(t_wolf3d *w, int i)
{
	double		dist_hor;
	double		dist_ver;

	dist_hor = sqrt(pow((w->cam->interh[i].x - w->cam->position.x), 2) + pow(
		(w->cam->interh[i].y - w->cam->position.y), 2));
	dist_ver = sqrt(pow((w->cam->interv[i].x - w->cam->position.x), 2) + pow(
		(w->cam->interv[i].y - w->cam->position.y), 2));
	if (dist_hor < dist_ver)
		w->cam->rays[i] = w->cam->interh[i];
	else
		w->cam->rays[i] = w->cam->interv[i];
	//printf("distance = %f\n", dist_hor);
	//printf("Point of intersections : x = %f, y = %f\n", w->cam->rays[i].x, w->cam->rays[i].y);
	//return (dist_hor);
	return ((dist_hor > dist_ver) ? dist_ver : dist_hor);
}

void					raycasting(t_wolf3d *w, int limit)
{
	int			i;
	double		angle;
	double 		dist;

	i = -1;
	while (++i < limit)
	{
		w->cam->rays[i].color = R_COLOR; // ray color (red)
		angle = w->cam->angle + (w->cam->fov / 2) - (i * w->cam->fov / limit);
		if (angle < 0)
			angle += 360;
		if (angle >= 360)
			angle -= 360;
		//if (angle >= 179.2 && angle <= 179.99) //huge problem on 179.2 ...
		//{
			//printf("angle == %f\n", angle);
			inter_ver(w, i, angle);
			inter_hor(w, i, angle);
			dist = get_distowall(w, i);
			limit == w->width ? render(w, i, dist) : 0;
		//}
	}
}
