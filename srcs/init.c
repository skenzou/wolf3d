/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 21:15:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/23 14:32:02 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			init_textures(t_wolf3d *w)
{
	w->textures[0] = create_image(w, "textures/eagle.xpm", 0, 0);
	w->textures[1] = create_image(w, "textures/bluestone.xpm", 0, 0);
	w->textures[2] = create_image(w, "textures/redbrick.xpm", 0, 0);
	w->textures[3] = create_image(w, "textures/greystone.xpm", 0, 0);
	w->textures[4] = create_image(w, "textures/sky.xpm", 0, 0);
	w->textures[5] = create_image(w, "textures/menu.xpm", 0, 0);
	w->textures[6] = create_image(w, "textures/options.xpm", 0, 0);
	w->textures[7] = create_image(w, "textures/xD.xpm", 0, 0);
	w->img = create_image(w, NULL, WIDTH, HEIGHT);
	w->minimap = create_image(w, NULL, 277, 277);
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
	cam->angle = 360.0;
	cam->speedangle = 5.0;
	cam->speedmove = 5.0;
	cam->fov = 60.0;
	cam->position.color = 0xff0000;
	cam->pangle = 0.0;
	cam->height = 500;
	return (cam);
}

void				init_wolf3d(int fd, t_wolf3d *w)
{
	w->map = create_map(fd);
	if (!(w->mlx_ptr = mlx_init()))
		exit(1);
	w->win_ptr = mlx_new_window(w->mlx_ptr, WIDTH, HEIGHT, "Wolf3d");
	!w->win_ptr ? exit(1) : 0;
	w->mini_h = BLOC_SIZE * w->map->h;
	w->mini_w = BLOC_SIZE * w->map->w;
	w->width = WIDTH;
	w->height = HEIGHT;
	w->nightmode = 1;
	w->cam = camera_init();
	place_player(w);
	w->menu = 1;
	w->scary = 0;
	w->sleep = 0;
	w->options = 0;
	w->texturelight = 50;
	w->floorlight = 100.;
	init_thread_data(w);
	init_textures(w);
	mlx_mouse_hook(w->win_ptr, &menu_event, w);
	mlx_hook(w->win_ptr, 6, 1L << 6, &camera_mov, w);
	mlx_hook(w->win_ptr, 2, 1L << 0, &key_pressed, w);
	mlx_loop_hook(w->mlx_ptr, &refresh, w);
	mlx_hook(w->win_ptr, 17, 1L << 17, &close_click, w);
}
