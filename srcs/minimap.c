/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:29:43 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/18 18:50:17 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_camera		*camera_init()
{
	t_camera		*cam;

	if (!(cam = (t_camera*)ft_memalloc(sizeof(*cam))))
		return (NULL);
	cam->radius = 5.0;
	cam->angle = 180.0;
	cam->speedangle = 5.0;
	cam->speedmove = 10.0;
	cam->fov = 60.0;
	cam->position.x = 128.0;
	cam->position.y = 128.0;
	cam->position.color = 0xff0000;
	cam->pangle = 0.0;
	return (cam);
}

static void		draw_square(t_wolf3d *w, t_point start)
{
	int		y;
	int		x;

	y = -1;
	while (++y <= 32)
	{
		x = -1;
		while (++x <= 32)
			mlx_pixel_put(w->mlx_ptr, w->win_ptr, x + start.x, y + start.y, start.color);
	}
}

void		draw_circle(t_wolf3d *w)
 {
 	float	angle;
 	 int		i;

 	angle = 0;
 	while (angle <= 2.0 * M_PI)
 	{
 		i = -1;
 		while (++i <= (int)w->cam->radius)
			mlx_pixel_put(w->mlx_ptr, w->win_ptr,  159 + i * cos(angle), 163 + i * sin(angle), 0x80ff0000);
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
				// if (!w->texture)
					draw_square(w, (t_point){.x = j * BLOC_SIZE, .y = i *
					BLOC_SIZE, .color = w->colors[w->map->board[i][j] % 4]});
				// else
				// 	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->textures
				// 	[w->map->board[i][j] % 4]->ptr,
				// 								j * BLOC_SIZE, i * BLOC_SIZE);
			}
}

void			draw_mmap(t_wolf3d *w)
{
	int		x;
	int		y;
	int		xoffset;
	int		yoffset;
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
		while(++i < 8)
		{
			if (x + i >= 0 && y + j >= 0 && y + j < w->map->h
					&& x + i < w->map->w && w->map->board[y + j][x + i] != 0)
				draw_square(w, (t_point){.x = xoffset + (i * 32),
								.y = yoffset + (j * 32), .color = 0x8000FF00});
			xoffset += 5;
		}
		yoffset += 5;
	}
}
