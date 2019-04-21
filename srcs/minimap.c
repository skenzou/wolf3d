/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:29:43 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/21 19:28:16 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_square(t_wolf3d *w, t_point start, int square_size)
{
	int		y;
	int		x;

	y = -1;
	while (++y <= square_size)
	{
		x = -1;
		while (++x <= square_size)
			put_pixel_img(w, x + start.x, y + start.y, start.color);
	}
}

static void		draw_circle(t_wolf3d *w)
{
	float	angle;
	int		i;

	angle = 0;
	while (angle <= 2.0 * M_PI)
	{
		i = -1;
		while (++i <= (int)w->cam->radius)
			put_pixel_img(w, 165 + i * cos(angle),
											165 + i * sin(angle), 0x80ff0000);
		angle += 0.005;
	}
}

void			draw_mmap(t_wolf3d *w, int yoffset)
{
	int		x;
	int		y;
	int		xoffset;
	int		j;
	int		i;

	draw_circle(w);
	yoffset = 0;
	x = (int)floor(w->cam->position.x / 64) - 4;
	y = (int)floor(w->cam->position.y / 64) - 4;
	j = -1;
	while (++j < 8 && (i = -1))
	{
		xoffset = 0;
		while (++i < 8)
		{
			if (x + i >= 0 && y + j >= 0 && y + j < w->map->h
					&& x + i < w->map->w && w->map->board[y + j][x + i] != 0)
				draw_square(w, (t_point){.x = xoffset + (i * 32),
							.y = yoffset + (j * 32), .color = 0x8000FF00}, 32);
			xoffset += 5;
		}
		yoffset += 5;
	}
}
