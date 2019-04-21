/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:20:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/21 18:05:45 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_sky(t_wolf3d *w, int x, int y_end)
{
	int y;
	int offset;
	int tex_y;

	y = 0;
	y_end = y_end > HEIGHT ? HEIGHT : y_end;
	while (y < y_end)
	{
		tex_y = y * (512. / HEIGHT) - 1;
		if (tex_y <= 0)
			tex_y = 1;
		offset = 512 * 4 * tex_y + (x % 512) * 4;
		ft_memcpy(w->img->data + 4 * WIDTH * y + x * 4,
					w->textures[4]->data + offset, 4);
		y++;
	}
}


int 	fetch_color(t_thread_data *d, int h_seen, int i, int y)
{
	int color;
	int tex_y;
	int tex_x;
	int index;
	int offset;

	index = d->w->map->board
		[(int)d->w->cam->rays[i].y / 64][(int)d->w->cam->rays[i].x / 64] % 4;
	if (!d->w->texture)
		return (d->w->colors[index]);
	tex_y = y * (64. / h_seen) -1;
	tex_x = d->inter ? (int)d->w->cam->rays[i].y % 64 : (int)d->w->cam->rays[i].x % 64;
	offset = 64 * 4 * tex_y + tex_x * 4;
	ft_memcpy((void *)&color, d->w->textures[d->direction]->data + offset, 4);
	return (color);
}

static inline void		render(t_wolf3d *w, int i, double depth, t_thread_data *d)
{
	int		h_seen;
	int		y;
	int		inc;

	h_seen = CAM_DIST * WALL_H / (depth * w->cos_table[i]);
	y = w->cam->height - (h_seen / 2) - 1;
	draw_sky(w, i, y + 151);
	inc = 0;
	while (++y < (w->cam->height + (h_seen / 2)))
		put_pixel_img(w, i, y + 150, fetch_color(d, h_seen, i, inc++));
	y--;
	while (++y < w->height)
		put_pixel_img(w, i, y + 150, GREY);
}

static inline void 		inter_hor(t_wolf3d *w, int i, double angle)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	double	tangent;

	tangent = w->tan_table[i] + 0.001;
	a.y = (angle <= 180) ? floor(w->cam->position.y / 64) *
	64 - 1 : floor(w->cam->position.y / 64) * 64 + 64;
	o.y = (angle < 180) ? -64 : 64;
	o.x = (angle < 90 || angle > 270) ? 64 / tangent : -64 / tangent;
	a.x = (angle < 359.95) ? w->cam->position.x + (w->cam->position.y - a.y) / tangent :
	w->cam->position.x + (w->cam->position.y - a.y) / -tangent;
	a.x = (angle >= 179.95 && angle <= 180) ? w->cam->position.x + (w->cam->position.y - a.y) / -tangent : a.x;
	if ((angle > 90 && angle <= 270 && (int)ceil(a.x) / 64 >= w->map->w) || a.x < 0 || a.x >= w->mini_w)
		a.x = (a.x < 0) ? 0 : w->mini_w - 64;
	while ((angle > 90 && angle <= 270 && w->map->board[(int)a.y / 64][(int)ceil(a.x) / 64] == 0)
		|| ((angle > 270 || angle <= 90) && w->map->board[(int)a.y / 64][(int)a.x / 64] == 0))
	{
		a.x += ((angle >= 90 && angle < 180) || angle >= 270) ? -o.x : o.x;
		a.y += o.y;
		if ((angle > 90 && angle <= 270 && (int)ceil(a.x) / 64 >= w->map->w) || a.x < 0 || a.x >= w->mini_w)
			a.x = (a.x < 0) ? 0 : w->mini_w - 64;
		if (a.y < 0 || a.y >= w->mini_h)
			break;
	}
	w->cam->interh[i].x = a.x;
	w->cam->interh[i].y = a.y;
}

static inline void 		inter_ver(t_wolf3d *w, int i, double angle)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	double	tangent;

	tangent = w->tan_table[i] + 0.001;
	a.x = (angle >= 90 && angle < 270) ? floor(w->cam->position.x / 64) *
	64 - 1 : floor(w->cam->position.x / 64) * 64 + 64;
	o.x = (angle > 90 && angle < 270) ? -64 : 64;
	o.y = (angle > 0 &&  angle < 180) ? -64 * tangent : 64 * tangent;
	a.y = (angle != 270 && angle != 90) ? w->cam->position.y + (w->cam->position.x - a.x)
	* tangent : w->cam->position.y + (w->cam->position.x - a.x) * -tangent;
	if ((angle < 180 && (int)ceil(a.y) / 64 > w->map->h) || a.y < 0 || a.y >=  w->mini_h)
		a.y = (a.y < 0) ? 0 : w->mini_h - 64;
	while ((angle < 180 && w->map->board[(int)ceil(a.y) / 64][(int)ceil(a.x) / 64] == 0)
		|| (angle >= 180 && w->map->board[(int)a.y / 64][(int)ceil(a.x) / 64] == 0))
	{
		a.y += ((angle > 90 && angle < 180) || angle > 270) ? -o.y : o.y;
		a.x += o.x;
		if ((angle < 180 && (int)ceil(a.y) / 64 > w->map->h) || a.y < 0 || a.y >=  w->mini_h)
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
		w->cam->rays[i].color = R_COLOR; // ray color (red)
		angle = w->cam->angle + w->cam->fov / 2 - (i * w->cam->fov / w->width);
		if (angle < 0)
			angle += 360;
		if (angle > 360)
			angle -= 360;
/*		if (i >= 569 && i <= w->width / 3) //huge problem on 179.2 ...
		{*/
			//printf("current i = %d angle = %f\n", i, angle);
			inter_ver(w, i, angle);
			inter_hor(w, i, angle);
			dist = get_distowall(w, i, d);
			render(w, i, dist, d);
		//}
		i++;
	}
	return (0);
}
