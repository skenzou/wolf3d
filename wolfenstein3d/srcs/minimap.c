#include "wolf3d.h"

t_camera	*camera_init(void)
{
	t_camera	*cam;
	unsigned int	i;

	if (!(cam = (t_camera*)malloc(sizeof(*cam))))
		return (NULL);
	cam->radius = 5.0;
	cam->angle  = 270.0;
	cam->speedangle = 10.0f;
	cam->speedmove = 20.0f;
	cam->fov = 60.0;
	cam->raylength = 300;
	cam->position.x = 128; 
	cam->position.y = 128;
	i = -1;
	return (cam);
}
void	projection2D(t_wolf3d *w)
{
	int 		i;

	i = -1;
	while (++i < WIDTH)
	{
		w->cam->rays[i].startPoint = w->cam->position;
		w->cam->rays[i].startPoint.color = 0xff0000;
		w->cam->rays[i].endPoint.color = 0xff0000;
		if (intersection(w, i))
			w->cam->rays[i].endPoint = w->cam->intersection;
		else
		{
			w->cam->rays[i].endPoint.x = w->cam->position.x + w->cam->raylength * Cos((w->cam->angle + w->cam->fov / 2) - (i * (w->cam->fov / WIDTH)));
			w->cam->rays[i].endPoint.y = w->cam->position.y + w->cam->raylength * Sin((w->cam->angle + w->cam->fov / 2) - (i * (w->cam->fov / WIDTH)));
		}
	}
}

void		draw_square(t_wolf3d *w, t_point start)
{
	int		y;
	int		x;

	y = -1;
	while (++y <= BLOC_SIZE)
	{
		x = -1;
		while (++x <= BLOC_SIZE)
			put_pixel_img(w, y + start.x, x + start.y, start.color);
	}
}
void			draw_circle(t_wolf3d *w)
{
	float	angle;
	int i;

	angle = 0;
	while (angle <= 2.0 * M_PI)
	{
		i = -1;
		while (++i <= (int)w->cam->radius)
			put_pixel_img(w, w->cam->position.x + i * cos(angle),
				w->cam->position.y + i * sin(angle), 0x00ff00);
		angle += 0.005;
	}
}

int 	intersection(t_wolf3d *w, int iteration)
{
	float			angle;
	int 			mapx;
	int 			mapy;
	unsigned int 	length;
	t_vec2f			dir;

	angle = (w->cam->angle + (w->cam->fov / 2) - (iteration * w->cam->fov / WIDTH));
	dir.x = Cos(angle);
	dir.y = Sin(angle);
	length = -1;
	while (++length < w->cam->raylength)
	{
		mapx = (int)(w->cam->position.x + (length * dir.x));
		mapy = (int)(w->cam->position.y + (length * dir.y));
		if (mapy / BLOC_SIZE < w->map->h && w->map->board[mapy / BLOC_SIZE][mapx / BLOC_SIZE])
		{
			w->cam->intersection.x = mapx;
			w->cam->intersection.y = mapy;
			return (1);
		}
	}
	return (0);

}

void	draw_mmap(t_wolf3d *w)
{
	unsigned int i;
	unsigned int j;

	i = -1;
	projection2D(w);
	draw_circle(w); // draw the camera;
	while (++i < WIDTH)
		//printf("start.x = %d start.y = %d end.y = %d end.x = %d\n", w->cam->rays[i].startPoint.x, w->cam->rays[i].startPoint.y, w->cam->rays[i].endPoint.y, w->cam->rays[i].endPoint.x);
		put_line(w, w->cam->rays[i].startPoint, w->cam->rays[i].endPoint);
	i = -1;
	while (++i < (unsigned int)w->map->h && (j = -1))
		while (++j < (unsigned int)w->map->w)
			if (w->map->board[i][j])
				draw_square(w, (t_point){.x = j * BLOC_SIZE, .y = i * BLOC_SIZE, .color = 0xffffff});
}
