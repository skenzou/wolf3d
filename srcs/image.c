/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:26:08 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/23 13:48:40 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				put_pixel_img(t_image *img, int x, int y, int color)
{
	int offset;

	offset = ((x + y * img->width) * img->bpp);
	if (x < img->width && x >= 0 && y < img->height && y >= 0)
	{
		img->data[offset] = color & 0xFF;
		img->data[offset + 1] = (color >> 8) & 0xFF;
		img->data[offset + 2] = (color >> 16) & 0xFF;
		img->data[offset + 3] = (color >> 24) & 0xFF;
	}
	return (1);
}

t_image			*create_image(t_wolf3d *w, char *path, int width, int height)
{
	t_image		*img;

	if (!(img = (t_image *)ft_memalloc(sizeof(t_image))))
		exit(1);
	if (path)
		img->ptr =
			mlx_xpm_file_to_image(w->mlx_ptr, path, &img->width, &img->height);
	else
	{
		img->ptr = mlx_new_image(w->mlx_ptr, width, height);
		img->width = width;
		img->height = height;
	}
	if (!(img->ptr))
		exit(1);
	img->data = mlx_get_data_addr(img->ptr,
			&img->bpp, &img->sizeline, &img->endian);
	img->bpp /= 8;
	return (img);
}
