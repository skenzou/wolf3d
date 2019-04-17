/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:29:43 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/17 12:02:30 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_camera		*camera_init()
{
	t_camera		*cam;

	if (!(cam = (t_camera*)ft_memalloc(sizeof(*cam))))
		return (NULL);
	cam->radius = 5.0;
	cam->angle = 360.0;
	cam->speedangle = 10.0;
	cam->speedmove = 40.0;
	cam->fov = 60.0;
	cam->position.x = 64.0;
	cam->position.y = 64.0;
	cam->position.color = 0xff0000;
	cam->pangle = 0.0;
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

// static void		draw_circle(t_wolf3d *w)
// {
// 	float	angle;
// 	int		i;
//
// 	angle = 0;
// 	while (angle <= 2.0 * M_PI)
// 	{
// 		i = -1;
// 		while (++i <= (int)w->cam->radius)
// 			put_pixel_img(w, w->cam->position.x + i * cos(angle),
// 				w->cam->position.y + i * sin(angle), 0x00ff00);
// 		angle += 0.005;
// 	}
// }

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
					BLOC_SIZE, .color = w->colors[w->map->board[i][j] % 4]});
				else
					mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->textures
					[w->map->board[i][j] % 4]->ptr,
												j * BLOC_SIZE, i * BLOC_SIZE);
			}
}

void			draw_mmap(t_wolf3d *w)
{
	int i;

	i = -1;
	raycasting(w);
// 	while (++i < w->width)
// 	{
// /*		printf("coordinates of the point received x = %f, y = %f\n", w->cam->rays[i].x, w->cam->rays[i].y);*/
// 		put_line(w, (t_point){.x = (int)w->cam->position.x, .y = (int)w->cam->
// 			position.y, .color = w->cam->position.color}, (t_point){.x = (int)
// 				w->cam->rays[i].x, .y = (int)w->cam->rays[i].y, .color =
// 				w->cam->rays[i].color});
// 	}
// 	if (!w->texture)
// 		draw_blocs(w);
	// draw_circle(w);
	// put_line(w, (t_point){.x = 0, .y = w->mini_h, .color = 0xffffff},
	// 			(t_point){.x = w->mini_w, .y = w->mini_h});
	// put_line(w, (t_point){.x = w->mini_w, .y = 0, .color = 0xffffff},
	// 			(t_point){.x = w->mini_w, .y = w->mini_h});
}
