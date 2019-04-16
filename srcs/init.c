/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 21:15:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/16 10:42:30 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static	void	init_textures(t_wolf3d *w)
{
	w->textures[0] = create_image(w, "textures/brick.xpm");
	w->textures[1] = create_image(w, "textures/wood.xpm");
	w->textures[2] = create_image(w, "textures/stone.xpm");
	w->textures[3] = create_image(w, "textures/w3d.wall.xpm");
	w->textures[4] = create_image(w, "textures/sky.xpm");
	w->colors[0] = ORANGE;
	w->colors[1] = PURPLE;
	w->colors[2] = BLUE;
	w->colors[3] = GREY;
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
	w->width = WIDTH - w->mini_w;
	w->height = HEIGHT - w->mini_h;
	w->cam = camera_init();
	init_textures(w);
	mlx_key_hook(w->win_ptr, &handle_key, w);
	mlx_hook(w->win_ptr, 6, 1L << 6, &camera_mov, w);
	//mlx_mouse_hook(w->win_ptr, &handle_mouse, w);
	//mlx_hook(w->win_ptr, 6, 1L << 6, &camera_mov, w);
	//mlx_hook(w->win_ptr, 2, 1L << 0, &handle_key, w);
	return (w);
}
