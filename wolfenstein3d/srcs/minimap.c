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
	cam->raylength = WIDTH;
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
	double		dist_w;
	double		dist_c;
	double		cam_h;
	double		h_seen;
	int 		y;
	int			hit;

	wall_h = 1000.0;
	cam_h = 500.0;
	dist_c = 50.0;
	hit = 0;
	limit = (l == 0) ? WIN_W : WIDTH_MM;
	i = -1;
	while (++i < limit)
	{
		w->cam->rays[i].startPoint = w->cam->position;
		w->cam->rays[i].startPoint.color = 0xff0000;
		w->cam->rays[i].endPoint.color = 0xff0000;
		// angle = (tempangle + w->cam->fov / 2) - (i * (w->cam->fov / limit));
		//printf("angle_minimap = %f\n", angle);
		if ((hit = intersection(w, i, l)))
			w->cam->rays[i].endPoint = w->cam->intersection;
		else
		{
			w->cam->rays[i].endPoint.x = w->cam->position.x + w->cam->raylength * tCos((w->cam->angle + w->cam->fov / 2) - (i * (w->cam->fov / limit)));
			w->cam->rays[i].endPoint.y = w->cam->position.y + w->cam->raylength * tSin((w->cam->angle + w->cam->fov / 2) - (i * (w->cam->fov / limit)));
		}
		if (l == 0)
		{
			perpdistwall = sqrt(pow((w->cam->position.x - w->cam->rays[i].endPoint.x), 2) + pow((w->cam->position.y - w->cam->rays[i].endPoint.y), 2));
			dist_w =  perpdistwall * tCos(30.0);
			h_seen = dist_c * wall_h / dist_w;
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

int 	intersection_hor(t_wolf3d *w, int iteration, t_vec2f *dir)
{
	t_point A;
	t_point	offset;
	int 	hit;

	while (hit == 0)
	{
		A.y = (dir->y < 0) ? floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE - 1 :
		ceil(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		offset.y = (dir->y < 0) ? -BLOC_SIZE : BLOC_SIZE;
		A.x = w->cam->position.x + (w->cam->position.y - y) / tTan(w->cam->fov);
		offset.x = BLOC_SIZE / tTan(w->cam->fov);
		if (w->map->board[A.y / BLOC_SIZE][A.x / BLOC_SIZE])
		{
			w->cam->intersection.x = A.x;
			w->cam->intersection.y = A.y;
			return (1);
		}
	}
}

int 	intersection_ver(t_wolf3d *w, int iteration, t_vec2f *dir)
{

}

int 	intersection(t_wolf3d *w, int iteration, int i)
{
	float			angle;
	int 			mapx;
	int 			mapy;
	unsigned int 	length;
	t_vec2f			dir;

	if (i == 1)
		angle = (w->cam->angle + (w->cam->fov / 2) - (iteration * w->cam->fov / WIDTH_MM));
	else
		angle = (w->cam->angle + (w->cam->fov / 2) - (iteration * w->cam->fov / WIN_W));
	dir.x = tCos(angle);
	dir.y = tSin(angle);
	length = -1;
	while (++length < w->cam->raylength)
	{
		mapx = (int)(w->cam->position.x + (length * dir.x));
		mapy = (int)(w->cam->position.y + (length * dir.y));
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
