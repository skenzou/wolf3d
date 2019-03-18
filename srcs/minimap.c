/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 13:02:34 by rkamegne          #+#    #+#             */
/*   Updated: 2019/03/18 15:17:48 by midrissi         ###   ########.fr       */
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

void			draw_minimap(t_wolf3d *w)
{
	int			x;
	int			y;
	int			x_s;
	int			y_s;

	y = -1;
	x_s = (WIN_W - w->map->w * MINIM_S) - 1;
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
		x_s = (WIN_W - w->map->w * MINIM_S) - 1;
		y_s += MINIM_S;
	}
}
