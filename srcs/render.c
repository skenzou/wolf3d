/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 17:38:24 by rkamegne          #+#    #+#             */
/*   Updated: 2019/04/23 13:48:55 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			draw_sky(t_wolf3d *w, int x, int y_end, int angle)
{
	int y;
	int offset;
	int tex_y;

	y = 0;
	y_end = y_end > HEIGHT ? HEIGHT : y_end;
	if (angle > 180)
		angle = 360 - angle;
	while (y < y_end)
	{
		tex_y = y * (512. / HEIGHT) - 1;
		if (tex_y <= 0)
			tex_y = 1;
		offset = 512 * 4 * tex_y + (angle % 512) * 4;
		ft_memcpy(w->img->data + 4 * WIDTH * y + x * 4,
					w->textures[4]->data + offset, 4);
		y++;
	}
}

static int		apply_shading(t_wolf3d *w, int color, double intensity)
{
	int		red;
	int		green;
	int		blue;

	if (intensity > 1 || !w->nightmode)
		return (color);
	red = ((color >> 16) & 0xff) * intensity;
	green = ((color >> 8) & 0xff) * intensity;
	blue = ((color & 0xff) * intensity);
	return ((red << 16) | (green << 8) | blue);
}

static int		fetch_color(t_thread_data *d, int h_seen, int y, double depth)
{
	int		color;
	int		tex_y;
	int		tex_x;
	int		offset;
	double	intensity;

	tex_y = y * (64. / h_seen) - 1;
	tex_x = d->inter ? (int)d->w->cam->rays[d->i].y % 64
					: (int)d->w->cam->rays[d->i].x % 64;
	offset = 64 * 4 * tex_y + tex_x * 4;
	ft_memcpy((void *)&color, d->w->textures[d->direction]->data + offset, 4);
	intensity = d->w->texturelight / (!depth ? 1. : depth);
	return (apply_shading(d->w, color, intensity));
}

void			render(double depth, t_thread_data *d, double angle)
{
	int		h_seen;
	int		y;
	int		inc;

	h_seen = CAM_DIST * WALL_H / (depth * d->w->cos_table[d->i]);
	y = d->w->cam->height - (h_seen / 2) - 1;
	draw_sky(d->w, d->i, y + 152, (int)angle);
	inc = 0;
	while (++y < (d->w->cam->height + (h_seen / 2)))
		put_pixel_img(d->w->img, d->i, y + 150,
										fetch_color(d, h_seen, inc++, depth));
	y--;
	while (++y < HEIGHT)
		put_pixel_img(d->w->img, d->i, y + 150,
			apply_shading(d->w, GREY, d->w->floorlight / (d->w->height - y)));
}
