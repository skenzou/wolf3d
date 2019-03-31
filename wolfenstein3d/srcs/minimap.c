/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:29:43 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/31 22:10:47 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_camera		*camera_init(t_wolf3d *w)
{
	t_camera		*cam;
	unsigned int	i;

	if (!(cam = (t_camera*)ft_memalloc(sizeof(*cam))))
		return (NULL);
	cam->radius = 5.0;
	cam->angle = 45.0;
	cam->speedangle = 10.0;
	cam->speedmove = 20.0;
	cam->fov = 60.0;
	cam->raylength = w->width;
	cam->position.x = 128;
	cam->position.y = 128;
	i = -1;
	return (cam);
}

static void		draw_square(t_wolf3d *w, t_point start)
{
	int		y;
	int		x;

	y = -1;
	while (++y <= BLOC_SIZE)
	{
		x = -1;
		while (++x <= BLOC_SIZE)
			put_pixel_img(w, y + start.x, x + start.y, start.color);
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
			put_pixel_img(w, w->cam->position.x + i * cos(angle),
				w->cam->position.y + i * sin(angle), 0x00ff00);
		angle += 0.005;
	}
}

void			draw_blocs(t_wolf3d *w)
{
	int i;
	int j;

	i = -1;
	while (++i < w->map->h && (j = -1))
		while (++j < w->map->w)
			if (w->map->board[i][j])
			{
				if (!w->texture)
					draw_square(w, (t_point){.x = j * BLOC_SIZE, .y = i *
					BLOC_SIZE, .color = w->colors[w->map->board[i][j] % 3]});
				else
					mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->textures
					[w->map->board[i][j] % 3]->ptr,
												j * BLOC_SIZE, i * BLOC_SIZE);
			}
}

void			draw_mmap(t_wolf3d *w)
{
	int i;

	i = -1;
	raycasting(w, w->mini_w);
	while (++i < w->mini_w)
		put_line(w, w->cam->rays[i].startpoint, w->cam->rays[i].endpoint);
	if (!w->texture)
		draw_blocs(w);
	draw_circle(w);
	put_line(w, (t_point){.x = 0, .y = w->mini_h, .color = 0xffffff},
				(t_point){.x = w->mini_w, .y = w->mini_h});
	put_line(w, (t_point){.x = w->mini_w, .y = 0, .color = 0xffffff},
				(t_point){.x = w->mini_w, .y = w->mini_h});
}
