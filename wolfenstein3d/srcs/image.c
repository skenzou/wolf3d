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
	create_image(w);
	//render(w);
	//ray_cast(w);
	draw_mmap(w);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->img->ptr,
																		0, 0);
}

void		create_image(t_wolf3d *w)
{
	w->img->ptr = mlx_new_image(w->mlx_ptr, WIDTH, HEIGHT);
	if (!(w->img->ptr))
		exit(1);
	w->img->data = mlx_get_data_addr(w->img->ptr,
			&w->img->bpp, &w->img->sizeline, &w->img->endian);
	w->img->bpp /= 8;
}