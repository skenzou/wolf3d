/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:20:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/16 14:29:03 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"


void	draw_sky(t_wolf3d *w, int x, int y_end)
{
	int y;
	int offset;
	int tex_y;

	y = 0;
	while (y < y_end)
	{
		tex_y = y * (512. / y_end) - 1;
		if (tex_y <= 0)
			tex_y = 1;
		// printf("texy: %d\n", tex_y);
		offset = 512 * 4 * tex_y + (x % 512) * 4;
		// printf("offset: %d\n", offset);
		ft_memcpy(w->img->data + 4 * WIDTH * y + (x + w->mini_w) * 4,
				w->textures[4]->data + offset, 4);
		y++;
	}
}


int 	fetch_color(t_wolf3d *w, int h_seen, int i, int y)
{
	int color;
	int tex_y;
	int tex_x;
	int index;
	int offset;

	index = w->map->board
		[(int)w->cam->rays[i].y / 64][(int)w->cam->rays[i].x / 64] % 4;
	if (!w->texture)
		return (w->colors[index]);
	tex_y = y * (64. / h_seen) -1;
	tex_x = w->inter ? (int)w->cam->rays[i].y % 64 : (int)w->cam->rays[i].x % 64;
	offset = 64 * 4 * tex_y + tex_x * 4;
	ft_memcpy((void *)&color, w->textures[index]->data + offset, 4);
	return (color);
}

static inline void		render(t_wolf3d *w, int i, double depth, double tab[])
{
	int		h_seen;
	int		y;
	// int		x;
	int		inc;

	h_seen = CAM_DIST * WALL_H / (depth * tab[i]);
	y = CAM_H - (h_seen / 2) - 1;
	// x = -1;
	// while (++x < y + 151)
	// 	put_pixel_img(w, i + w->mini_w, x, 0x0010ff);
	draw_sky(w, i, y + 151);
	inc = 0;
	while (++y < (CAM_H + (h_seen / 2)))
		put_pixel_img(w, i + w->mini_w, y + 150, fetch_color(w, h_seen, i, inc++));
	while (++y < w->width)
		put_pixel_img(w, i + w->mini_w, y + 150, GREY);
}

static inline void 		inter_hor(t_wolf3d *w, int i, double angle, double tab[])
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	double	tangent;

	tangent = tab[i] + 0.001;
	a.y = (angle <= 180) ? floor(w->cam->position.y / 64) *
	64 - 1 : floor(w->cam->position.y / 64) * 64 + 64;
	o.y = (angle < 180) ? -64 : 64;
	o.x = (angle < 90 || angle > 270) ? 64 / tangent : -64 / tangent;
	a.x = (angle != 180.0 && angle < 359.97) ? w->cam->position.x + (w->cam->position.y - a.y) / tangent :
	w->cam->position.x + (w->cam->position.y - a.y) / -tangent;
/*	a.x = ((angle >= 179.965197 && angle <= 180) && angle != 0) ? w->cam->position.x + (w->cam->position.y - a.y) / -tangent : a.x;*/
	if (a.x < 0 || a.x >= w->mini_w)
		a.x = (a.x < 0) ? 0 : w->mini_w - 1;
	while (w->map->board[(int)a.y / 64][(int)a.x / 64] == 0)
	{
		a.x += ((angle >= 90 && angle < 180) || angle >= 270) ? -o.x : o.x;
		a.y += o.y;
		if (a.x < 0 || a.x >=  w->mini_w)
			a.x = (a.x < 0) ? 0 : w->mini_w - 1;
		if (a.y < 0 || a.y >= w->mini_h)
			break;
	}
	w->cam->interh[i].x = a.x;
	w->cam->interh[i].y = a.y;
}

static inline void 		inter_ver(t_wolf3d *w, int i, double angle, double tab[])
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	double	tangent;

	tangent = tab[i] + 0.001;
	a.x = (angle >= 90 && angle < 270) ? floor(w->cam->position.x / 64) *
	64 - 1 : floor(w->cam->position.x / 64) * 64 + 64;
	o.x = (angle > 90 && angle < 270) ? -64 : 64;
	o.y = (angle > 0 &&  angle < 180) ? -64 * tangent : 64 * tangent;
	a.y = (angle != 270 && angle != 90) ? w->cam->position.y + (w->cam->position.x - a.x)
	* tangent : w->cam->position.y + (w->cam->position.x - a.x) * -tangent;
	if (a.y < 0 || a.y >=  w->mini_h)
		a.y = (a.y < 0) ? 0 : w->mini_h - 1;
	while (w->map->board[(int)a.y / 64][(int)a.x / 64] == 0)
	{
		a.y += ((angle > 90 && angle < 180) || angle > 270) ? -o.y : o.y;
		a.x += o.x;
		if (a.y < 0 || a.y >=  w->mini_h)
			a.y = (a.y < 0) ? 0 : w->mini_h - 1;
		if (a.x < 0 || a.x > w->mini_w - 1)
			break;
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
	{
		w->cam->rays[i] = w->cam->interh[i];
		w->inter = 0;
	}
	else
	{
		w->cam->rays[i] = w->cam->interv[i];
		w->inter = 1;
	}
	return ((dist_hor > dist_ver) ? dist_ver : dist_hor);
}

void					raycasting(t_wolf3d *w)
{
	int			i;
	double		angle;
	double 		dist;
	double		cos_table[w->width];
	double		tan_table[w->width];

	i = -1;
	cos_lookuptable(w, cos_table);
	tan_lookuptable(w, tan_table);
	while (++i < w->width)
	{
		w->cam->rays[i].color = R_COLOR; // ray color (red)
		angle = w->cam->angle + w->cam->fov / 2 - (i * w->cam->fov / w->width);
		if (angle < 0)
			angle += 360;
		if (angle > 360)
			angle -= 360;
/*		if (i >= 569 && i <= w->width / 3) //huge problem on 179.2 ...
		{*/
			//printf("current i = %d angle = %f\n", i, angle);
			inter_ver(w, i, angle, tan_table);
			inter_hor(w, i, angle, tan_table);
			dist = get_distowall(w, i);
			render(w, i, dist, cos_table);
		//}
	}
}
