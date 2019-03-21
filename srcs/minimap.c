/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 13:02:34 by rkamegne          #+#    #+#             */
/*   Updated: 2019/03/21 17:01:26 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_square(t_wolf3d *w, t_point start)
{
	int		y;
	int		x;

	y = -1;
	while (++y <= MINIM_S)
	{
		x = -1;
		while (++x <= MINIM_S)
		{
			if (x + start.x == start.x || y + start.y == start.y || x == MINIM_S
			|| y == MINIM_S)
				put_pixel_img(w, y + start.x, x + start.y, LIGHTRED);
			else
				put_pixel_img(w, y + start.x, x + start.y, start.color);
		}
	}
}

static void			draw_vision(t_wolf3d *w, int x_c, int y_c)
{
	double	angle;
	double	ang_e;
	double	i;
	double	r;
	int		x;
	int		y;

	angle = w->ang_s;
	ang_e = w->ang_s + (60.0 * M_PI / 180);
	r = w->map->w * MINIM_S;
	while (angle <= ang_e)
	{
		i = -1;
		while (++i <= r)
		{
			x = x_c + i * cos(angle);
			y = y_c + i * sin(angle);
			if (x > 0 && y > 0 && x < w->map->w * MINIM_S && y < w->map->h *
				MINIM_S && w->map->board[y / MINIM_S][x / MINIM_S] != 0)
				break ;
			if (x > 0 && x < w->map->w * MINIM_S && y > 0 && y < w->map->h
				* MINIM_S)
				put_pixel_img(w, x, y, 0x880055);
		}
		angle += 60.0 / (w->map->w * MINIM_S) / 180;
	}
}

static void		draw_wall(t_wolf3d *w, int x, int color)
{
	int y = 200;
	while (y < 500)
	{
		put_pixel_img(w, x,y, color);
		y++;
	}
}

static void 	draw_game(t_wolf3d *w, int x_c, int y_c)
{
	double	angle;
	double	ang_e;
	double	i;
	double	r;
	int		x;
	int		y;
	int offset = 0;

	angle = w->ang_s;
	ang_e = w->ang_s + (60.0 * M_PI / 180);
	r = w->map->w * MINIM_S;
	while (angle <= ang_e)
	{
		i = -1;
		while (++i <= r)
		{
			x = x_c + i * cos(angle);
			y = y_c + i * sin(angle);
			if (x > 0 && y > 0 && x < w->map->w * MINIM_S && y < w->map->h *
				MINIM_S && w->map->board[y / MINIM_S][x / MINIM_S] != 0)
			{
				if (offset < 1200 && w->map->board[y / MINIM_S][x / MINIM_S] != 0)
				{
					offset += 1;
					draw_wall(w, offset, offset * 0x11ac11);
				}
					break ;
			}
			if (x > 0 && x < w->map->w * MINIM_S && y > 0 && y < w->map->h
				* MINIM_S)
				put_pixel_img(w, x, y, 0x880055);
		}
		angle += 60.0 / (w->map->w * MINIM_S) / 180;
	}
}

int				camera_mov(int x, int y, t_wolf3d *w)
{
	// int		dx;
	// int		dy;
	// double	hyp;
	// double	cos_ang;
	// double	angle;
	//
	// dx = x - w->xpos;
	// dy = y - w->ypos;
	// hyp = sqrt(pow(dx, 2) + pow(dy, 2));
	// cos_ang = fabs(dx / hyp);
	// angle = acos(cos_ang);
	// if (dx < 0 && dy < 0)
	// 	w->ang_s = angle + M_PI;
	// if (dx > 0 && dy < 0)
	// 	w->ang_s = -angle;
	// if (dx < 0 && dy > 0)
	// 	w->ang_s = -angle - M_PI;
	// if (dx >= 0 && dy >= 0)
	// 	w->ang_s = angle;
	w->ang_s = atan2(y,x);
	process(w);
	return (0);
}

void			draw_circle(t_wolf3d *w, int x_c, int y_c)
{
	float	angle;
	float	i;
	int		j;
	float	tmp;

	j = 0;
	angle = 0;
	tmp = M_PI / 6.0;
	while (angle <= 2.0 * M_PI)
	{
		i = -1;
		if (angle > tmp && ++j)
			tmp += M_PI / 6.0;
		while (++i <= (float)MINIM_S / 3.0)
			put_pixel_img(w, x_c + i * cos(angle), y_c + i * sin(angle),
																	DARKBLUE);
		angle += 0.005;
	}
}

void			draw_minimap(t_wolf3d *w)
{
	int			x;
	int			y;
	int			x_s;
	int			y_s;

	y = -1;
	x_s = 1;
	y_s = 1;
	while (++y < w->map->h && (x = -1))
	{
		while (++x < w->map->w)
		{
			if (w->map->board[y][x] == 0)
				draw_square(w, (t_point){.x = x_s, .y = y_s,
					.color = 0xa9a9a9});
			else
				draw_square(w, (t_point){.x = x_s, .y = y_s,
					.color = 0x00Fb00});
			x_s += MINIM_S;
		}
		x_s = 1;
		y_s += MINIM_S;
	}
	x = 1 + w->xpos * MINIM_S + MINIM_S / 2;
	y = 1 + w->ypos * MINIM_S + MINIM_S / 2;
	draw_circle(w, x, y);
	draw_vision(w, x, y);
	draw_game(w, x, y);
}
