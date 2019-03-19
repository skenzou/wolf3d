/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 13:02:34 by rkamegne          #+#    #+#             */
/*   Updated: 2019/03/19 12:05:45 by midrissi         ###   ########.fr       */
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
	float	angle;
	float	i;
	float	r;
	int		x;
	int		y;

	angle = M_PI * 4.0 / 3.0;
	r = w->map->w * MINIM_S;
	while (angle <= M_PI * 5.0 / 3.0)
	{
		i = -1;
		while (++i <= r)
		{
			x = x_c + i * cos(angle);
			y = y_c + i * sin(angle);
			if (x > 0 && y > 0 && w->map->board[y / MINIM_S][x / MINIM_S] != 0)
				break ;
			if (x > 0 && x < w->map->w * MINIM_S && y > 0 && y < w->map->h
				* MINIM_S)
				put_pixel_img(w, x, y, DARKBLUE);
		}
		angle += 0.0005;
	}
}

int				camera_mov(int x, int y, t_wolf3d *w)
{
	(void)x;
	(void)y;
	(void)w;
	return (1);
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
}
