/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:26:08 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/19 13:20:58 by midrissi         ###   ########.fr       */
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

void		launch_threads(t_wolf3d *w)
{
	pthread_attr_t	attr;
	int				err;
	int				i;

	i = 0;
	pthread_attr_init(&attr);
	while (i < TNUM)
	{
		err = pthread_create(&(w->tids[i]), &attr, raycasting,
															&w->tdata[i]);
		if (err)
		{
			perror("thread error");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < TNUM)
		pthread_join(w->tids[i++], NULL);
}

int			process(t_wolf3d *w)
{
	if (w->img->ptr)
		mlx_destroy_image(w->mlx_ptr, w->img->ptr);
	w->img = create_image(w, NULL);
	draw_sky(w);
	launch_threads(w);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->img->ptr, 0, 0);
	draw_mmap(w);
	return (0);
	// if (w->texture)
	// 	draw_blocs(w);
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
