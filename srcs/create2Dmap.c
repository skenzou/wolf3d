/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create2Dmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 13:02:34 by rkamegne          #+#    #+#             */
/*   Updated: 2019/03/18 13:44:27 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_square(t_window *w, int side, color)
{
	int		i;
	int		j;

	i = w->y - 1;
	while (++i <= side)
	{
		j = w->x - 1;
		while (++j <= side)
		mlx_put_pixel_img(w->image_str, i, j, color);
	}
}


void	create2Dmap(t_map *map)
{
	t_window	win;
	int			specs[3];
	int			x;
	int			y;

	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win_ptr, WIDTH, HEIGHT, "wolf3D");
	win.image_ptr = mlx_new_image(win.mlx_ptr, map->w * 100, map->h * 100);
	win.image_str = mlx_get_data_addr(win.image_ptr, &specs[0], &specs[1],
			&specs[2]);
	y = 1;
	while (++y < map->h && (x = -1))
	{
		win.x = 0;
		while (++x < map->w)
		{
			if (map->grid[y][x] == 0)
				draw_square(&win, 20

}
