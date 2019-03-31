/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 16:20:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/31 21:55:34 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline int		fetch_color(t_wolf3d *w)
{
	return (w->colors[(w->map->board[w->cam->intersection.y / BLOC_SIZE]
									[w->cam->intersection.x / BLOC_SIZE]) % 3]);
}

// static inline int		fetch_texture(t_wolf3d *w)
// {
// 	return ()
// }

static inline void		render(t_wolf3d *w, int i, int hit)
{
	int		h_seen;
	t_point	raytravel;
	double	depth;
	int		y;
	int		x;

	raytravel.y = w->cam->rays[i].endpoint.y - w->cam->position.y;
	raytravel.x = w->cam->rays[i].endpoint.x - w->cam->position.x;
	depth = raytravel.x * tcos(w->cam->angle)
											+ raytravel.y * tsin(w->cam->angle);
	h_seen = CAM_DIST * WALL_H / depth;
	y = CAM_H - (h_seen / 2) - 1;
	x = -1;
	while (++x < y + 151)
		put_pixel_img(w, w->width - i + w->mini_w, x, 0x09e4ef);
	if (hit == 1)
		while (++y < (CAM_H + (h_seen / 2)))
			put_pixel_img(w, w->width - i + w->mini_w, y + 150, fetch_color(w));
	while (++y < w->width)
		put_pixel_img(w, w->width - i + w->mini_w, y + 150, GREY);
}

static inline int		intersection(t_wolf3d *w, int i, t_vec2f *dir)
{
	int				mapx;
	int				mapy;
	unsigned int	length;

	length = -1;
	i = i == w->mini_w ? 1 : 0;
	while (++length < w->cam->raylength)
	{
		mapx = (int)(w->cam->position.x + (length * dir->x));
		mapy = (int)(w->cam->position.y + (length * dir->y));
		if ((mapx / BLOC_SIZE >= 0 && mapx / BLOC_SIZE < w->map->w &&
		mapy / BLOC_SIZE < w->map->h && mapy / BLOC_SIZE >= 0 &&
		w->map->board[mapy / BLOC_SIZE][mapx / BLOC_SIZE])
		|| (i == 1 && (mapy > w->mini_h || mapy <= 0 || mapx > w->mini_w ||
		mapx <= 0)))
		{
			w->cam->intersection.x = mapx;
			w->cam->intersection.y = mapy;
			return (1);
		}
	}
	return (0);
}

void					raycasting(t_wolf3d *w, int limit)
{
	int			i;
	int			hit;
	t_vec2f		dir;
	double		angle;

	i = -1;
	while (++i < limit && !(hit = 0))
	{
		w->cam->rays[i].startpoint = w->cam->position;
		w->cam->rays[i].startpoint.color = 0xff0000;
		angle = (w->cam->angle + (w->cam->fov / 2)
											- (i * w->cam->fov / limit));
		dir.x = tcos(angle);
		dir.y = tsin(angle);
		if ((hit = intersection(w, limit, &dir)))
			w->cam->rays[i].endpoint = w->cam->intersection;
		else
		{
			w->cam->rays[i].endpoint.x = w->cam->position.x + w->cam->raylength
				* dir.x;
			w->cam->rays[i].endpoint.y = w->cam->position.y + w->cam->raylength
				* dir.y;
		}
		limit == w->width ? render(w, i, hit) : 0;
	}
}
