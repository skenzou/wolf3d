/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 09:45:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/22 12:53:23 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		check_error(int argc)
{
	if (argc != 2)
	{
		ft_putendl_fd(ANSI_RED "usage: ./wolf3d <map>", 2);
		exit(1);
	}
}

t_wolf3d		*init_wolf3d(int fd)
{
	t_wolf3d *w;

	w = (t_wolf3d *)ft_memalloc(sizeof(t_wolf3d));
	w->map = create_map(fd);
	if (!(w->mlx_ptr = mlx_init()))
		exit(1);
	w->win_ptr = mlx_new_window(w->mlx_ptr, WIN_W, WIN_H, "Wolf3d");
	!w->win_ptr ? exit(1) : 0;
	if (!(w->img = (t_image *)ft_memalloc(sizeof(t_image))))
		exit(1);
	//mlx_key_hook(w->win_ptr, &handle_key, w);
	mlx_mouse_hook(w->win_ptr, &handle_mouse, w);
	mlx_hook(w->win_ptr, 6, 1L << 6, &camera_mov, w);
	mlx_hook(w->win_ptr, 2, 1L << 0, &handle_key, w);
	w->ypos = 1;
	w->xpos = 1;
	w->xdir = -1.0;
	w->ydir = 0.0;
	w->xplane = 0.0;
	w->yplane = 0.66;
	w->posx = 22.0;
	w->posy = 11.5;
	w->ang_s = 60;
	return (w);
}

void			print_map(t_wolf3d *w)
{
	int y;
	int x;

	y = -1;
	while (++y < w->map->h && (x = -1))
	{
		while (++x < w->map->w)
			ft_printf("%2d", w->map->board[y][x]);
		ft_printf("\n");
	}
}

int				main(int argc, char **argv)
{
	t_wolf3d	*w;
	int			fd;

	check_error(argc);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("error");
		return (0);
	}
	w = init_wolf3d(fd);
	print_map(w);
	process(w);
	// render(w);
	mlx_loop(w->mlx_ptr);
	return (0);
}
