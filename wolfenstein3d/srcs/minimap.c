#include "wolf3d.h"

t_camera	*camera_init(void)
{
	t_camera	*cam;
	unsigned int	i;

	if (!(cam = (t_camera*)malloc(sizeof(*cam))))
		return (NULL);
	cam->radius = 5.0f;
	cam->angle  = 45.0f;
	cam->speedangle = 10.0f;
	cam->speedmove = 20.0f;
	cam->fov = 60.0f;
	cam->raylength = WIN_W;
	cam->position.x = 128;
	cam->position.y = 128;
	i = -1;
	return (cam);
}

void	projection(t_wolf3d *w, int l)
{
	int 		i;
	int			limit;
	double		wall_h;
	double		perpdistwall;
	//double		dist_w;
	double		distortion;
	double		dist_c;
	double		cam_h;
	double		h_seen;
	int 		y;
	int			hit;
	t_vec2f		dir;
	double		angle;
	t_point		raytravel;
	double		depth;

	wall_h = 1000.0;
	cam_h = 500.0;
	dist_c = 50.0;
	hit = 0;
	limit = (l == 0) ? WIN_W : WIDTH_MM;
	i = -1;
	perpdistwall = WIN_W / 2 / tTan(w->cam->fov / 2);
	while (++i < limit)
	{
		w->cam->rays[i].startPoint = w->cam->position;
		w->cam->rays[i].startPoint.color = 0xff0000;
		w->cam->rays[i].endPoint.color = 0xff0000;
		if (l == 1)
			angle = (w->cam->angle + (w->cam->fov / 2) - (i * w->cam->fov / WIDTH_MM));
		else
			angle = (w->cam->angle + (w->cam->fov / 2) - (i * w->cam->fov / WIN_W));
		dir.x = tCos(angle);
		dir.y = tSin(angle);
		if ((hit = intersection(w, l, &dir)))
			w->cam->rays[i].endPoint = w->cam->intersection;
		else
		{
			w->cam->rays[i].endPoint.x = w->cam->position.x + w->cam->raylength * tCos((w->cam->angle + w->cam->fov / 2) - (i * (w->cam->fov / limit)));
			w->cam->rays[i].endPoint.y = w->cam->position.y + w->cam->raylength * tSin((w->cam->angle + w->cam->fov / 2) - (i * (w->cam->fov / limit)));
		}
		if (l == 0)
		{
			raytravel.y = w->cam->rays[i].endPoint.y - w->cam->position.y;
			raytravel.x = w->cam->rays[i].endPoint.x - w->cam->position.x;
			depth = raytravel.x * dir.x + raytravel.y * dir.y;
			//
			// dist_w = sqrt(pow((w->cam->position.x - w->cam->rays[i].endPoint.x), 2) + pow((w->cam->position.y - w->cam->rays[i].endPoint.y), 2));
			distortion = depth * tCos(w->cam->fov / 2 - (i * w->cam->fov / WIN_W));
			// if (distortion)
			h_seen = dist_c * wall_h / distortion;
			//printf("h_seen = %f\n", h_seen);
			y = cam_h - (h_seen / 2) - 1;
			if (hit == 1)
				while (++y < (cam_h + (h_seen / 2)))
					put_pixel_img(w, WIN_W - i + WIDTH_MM, y + 150, 0xff0000);
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

int 	intersection(t_wolf3d *w, int i, t_vec2f *dir)
{
	int 			mapx;
	int 			mapy;
	unsigned int 	length;
	length = -1;
	while (++length < w->cam->raylength)
	{
		mapx = (int)(w->cam->position.x + (length * dir->x));
		mapy = (int)(w->cam->position.y + (length * dir->y));
		if ((mapy / BLOC_SIZE < w->map->h && w->map->board[mapy / BLOC_SIZE][mapx / BLOC_SIZE]) || (i == 1 && mapy >= HEIGHT_MM))
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
	projection(w,1);
	draw_circle(w); // draw the camera;
	while (++i < WIDTH_MM)
		//printf("start.x = %d start.y = %d end.y = %d end.x = %d\n", w->cam->rays[i].startPoint.x, w->cam->rays[i].startPoint.y, w->cam->rays[i].endPoint.y, w->cam->rays[i].endPoint.x);
		put_line(w, w->cam->rays[i].startPoint, w->cam->rays[i].endPoint);
	i = -1;
	while (++i < (unsigned int)w->map->h && (j = -1))
		while (++j < (unsigned int)w->map->w)
			if (w->map->board[i][j])
				draw_square(w, (t_point){.x = j * BLOC_SIZE, .y = i * BLOC_SIZE, .color = 0xffffff});
	projection(w,0);
}
