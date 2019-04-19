/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 21:15:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/19 13:23:49 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	init_textures(t_wolf3d *w)
{
	w->textures[0] = create_image(w, "textures/brick.xpm");
	w->textures[1] = create_image(w, "textures/test.xpm");
	w->textures[2] = create_image(w, "textures/bluestone.xpm");
	w->textures[3] = create_image(w, "textures/greystone.xpm");
	w->textures[4] = create_image(w, "textures/sky.xpm");
	w->textures[5] = create_image(w, "textures/metal.xpm");
	w->colors[0] = ORANGE;
	w->colors[1] = PURPLE;
	w->colors[2] = BLUE;
	w->colors[3] = GREY;
}

void		init_thread_data(t_wolf3d *w)
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
	cam->position.x = 256.0;
	cam->position.y = 256.0;
	cam->position.color = 0xff0000;
	cam->pangle = 0.0;
	cam->height = 500;
	return (cam);
}


t_wolf3d		*init_wolf3d(int fd)
{
	t_wolf3d *w;

	w = (t_wolf3d *)ft_memalloc(sizeof(t_wolf3d));
	w->map = create_map(fd);
	if (!(w->mlx_ptr = mlx_init()))
		exit(1);
	w->win_ptr = mlx_new_window(w->mlx_ptr, WIDTH, HEIGHT, "Wolf3d");
	!w->win_ptr ? exit(1) : 0;
	w->img = create_image(w, NULL);
	w->texture = 1;
	w->mini_h = BLOC_SIZE * w->map->h;
	w->mini_w = BLOC_SIZE * w->map->w;
	w->width = WIDTH;
	w->height = HEIGHT;
	w->cam = camera_init();
	init_thread_data(w);
	init_textures(w);
	//mlx_key_hook(w->win_ptr, &handle_key, w);
	mlx_hook(w->win_ptr, 6, 1L << 6, &camera_mov, w);
	//mlx_mouse_hook(w->win_ptr, &handle_mouse, w);
	mlx_hook(w->win_ptr, 2, 1L << 0, &key_pressed, w);
	mlx_loop_hook(w->mlx_ptr, &process, w);
	return (w);
}
