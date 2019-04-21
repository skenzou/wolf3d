/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 21:15:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/21 20:45:28 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			init_textures(t_wolf3d *w)
{
	w->textures[0] = create_image(w, "textures/eagle.xpm");
	w->textures[1] = create_image(w, "textures/bluestone.xpm");
	w->textures[2] = create_image(w, "textures/redbrick.xpm");
	w->textures[3] = create_image(w, "textures/greystone.xpm");
	w->textures[4] = create_image(w, "textures/sky.xpm");
	w->textures[5] = create_image(w, "textures/menu.xpm");
}

static void			init_thread_data(t_wolf3d *w)
{
	int i;
	int x_s;
	int x_end;

	i = 0;
	x_end = WIDTH / TNUM;
	x_s = 0;
	while (i < TNUM)
	{
		w->tdata[i++] = (t_thread_data){.x = x_s, .y = 0, .y_end = HEIGHT,
			.x_end = x_end, .w = w};
		x_s += (WIDTH / TNUM);
		x_end += (WIDTH / TNUM);
	}
}

static void			place_player(t_wolf3d *w)
{
	int i;
	int j;

	j = -1;
	while (++j < w->map->h && (i = -1))
		while (++i < w->map->w)
			if (!w->map->board[j][i])
			{
				w->cam->position.x = i * 64 + 20;
				w->cam->position.y = j * 64 + 20;
				return ;
			}
	ft_putendl_fd(ANSI_RED "Could not place the player because the map is full,\
	please choose a valid map", 2);
	exit(1);
}

static t_camera		*camera_init(void)
{
	t_camera		*cam;

	if (!(cam = (t_camera*)ft_memalloc(sizeof(t_camera))))
		exit(1);
	cam->radius = 5.0;
	cam->angle = 180.0;
	cam->speedangle = 5.0;
	cam->speedmove = 5.0;
	cam->fov = 60.0;
	cam->position.color = 0xff0000;
	cam->pangle = 0.0;
	cam->height = 500;
	return (cam);
}

t_wolf3d			*init_wolf3d(int fd)
{
	t_wolf3d *w;

	w = (t_wolf3d *)ft_memalloc(sizeof(t_wolf3d));
	w->map = create_map(fd);
	if (!(w->mlx_ptr = mlx_init()))
		exit(1);
	w->win_ptr = mlx_new_window(w->mlx_ptr, WIDTH, HEIGHT, "Wolf3d");
	!w->win_ptr ? exit(1) : 0;
	w->img = create_image(w, NULL);
	w->mini_h = BLOC_SIZE * w->map->h;
	w->mini_w = BLOC_SIZE * w->map->w;
	w->width = WIDTH;
	w->height = HEIGHT;
	w->cam = camera_init();
	place_player(w);
	w->menu = 1;
	init_thread_data(w);
	init_textures(w);
	mlx_mouse_hook(w->win_ptr, &menu_event, w);
	mlx_hook(w->win_ptr, 6, 1L << 6, &camera_mov, w);
	mlx_hook(w->win_ptr, 2, 1L << 0, &key_pressed, w);
	mlx_loop_hook(w->mlx_ptr, &refresh, w);
	return (w);
}
