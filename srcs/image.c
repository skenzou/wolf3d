/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:26:08 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/15 18:27:50 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			put_pixel_img(t_wolf3d *w, int x, int y, int color)
{
	int offset;

	offset = ((x + y * WIDTH) * w->img->bpp);
	if (x < WIDTH && x > 0 && y < HEIGHT && y > 0)
	{
		w->img->data[offset] = color & 0xFF;
		w->img->data[offset + 1] = (color >> 8) & 0xFF;
		w->img->data[offset + 2] = (color >> 16) & 0xFF;
	}
	return (1);
}

void		process(t_wolf3d *w)
{
	if (w->img->ptr)
		mlx_destroy_image(w->mlx_ptr, w->img->ptr);
	w->img = create_image(w, NULL);
	draw_mmap(w);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->img->ptr,
																		0, 0);
	if (w->texture)
		draw_blocs(w);
}

t_image			*create_image(t_wolf3d *w, char *path)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
		exit(1);
	if (path)
		img->ptr =
			mlx_xpm_file_to_image(w->mlx_ptr, path, &img->width, &img->height);
	else
		img->ptr = mlx_new_image(w->mlx_ptr, WIDTH, HEIGHT);
	if (!(img->ptr))
		exit(1);
	img->data = mlx_get_data_addr(img->ptr,
			&img->bpp, &img->sizeline, &img->endian);
	img->bpp /= 8;
	return (img);
}
