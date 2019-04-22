/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:38:24 by rkamegne          #+#    #+#             */
/*   Updated: 2019/04/22 18:34:34 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_sky(t_wolf3d *w, int x, int y_end)
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

static	int	apply_shading(int color, double intensity)
{
	int		red;
	int		green;
	int		blue;

	red = ((color >> 16) & 0xff) * intensity;
	green = ((color >> 8) & 0xff) * intensity;
	blue = ((color & 0xff) * intensity);
	return ((red << 16) | (green << 8) | blue);
}

static	int	fetch_color(t_thread_data *d, int h_seen, int i, int y)
{
	int		color;
	int		tex_y;
	int		tex_x;
	int		offset;
	double	intensity;

	tex_y = y * (64. / h_seen) - 1;
	tex_x = d->inter ? (int)d->w->cam->rays[i].y % 64 :
	(int)d->w->cam->rays[i].x % 64;
	offset = 64 * 4 * tex_y + tex_x * 4;
	ft_memcpy((void *)&color, d->w->textures[d->direction]->data + offset, 4);
	if (d->depth > 0 && d->depth < 350)
		intensity = 1;
	else
		intensity = 0.25;
	color = apply_shading(color, intensity);
	return (color);
}

void		render(t_wolf3d *w, int i, double depth, t_thread_data *d)
{
	int		h_seen;
	int		y;
	int		inc;

	h_seen = CAM_DIST * WALL_H / (depth * w->cos_table[i]);
	y = w->cam->height - (h_seen / 2) - 1;
	draw_sky(w, i, y + 152);
	inc = 0;
	d->depth = depth;
	while (++y < (w->cam->height + (h_seen / 2)))
		put_pixel_img(w->img, i, y + 150, fetch_color(d, h_seen, i,
					inc++));
	y--;
	while (++y < w->height)
		put_pixel_img(w->img, i, y + 150, GREY);
}
