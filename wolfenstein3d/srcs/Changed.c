angle = (w->cam->angle + (w->cam->fov / 2)
									- (i * w->cam->fov / limit));
dir.x = tcos(angle);
dir.y = tsin(angle);

static inline int		intersection(t_wolf3d *w, int i, t_vec2f *dir)
{
	int				mapx;
	int				mapy;
	unsigned int	length;

	length = -1;
	i = i == w->mini_w ? 1 : 0;
	while (++length < w->cam->raylength)
	{
		mapx = (int)(w->cam->position.x + (length * dir->x));
		mapy = (int)(w->cam->position.y + (length * dir->y));
		if ((mapx / BLOC_SIZE >= 0 && mapx / BLOC_SIZE < w->map->w &&
		mapy / BLOC_SIZE < w->map->h && mapy / BLOC_SIZE >= 0 &&
		w->map->board[mapy / BLOC_SIZE][mapx / BLOC_SIZE])
		|| (i == 1 && (mapy > w->mini_h || mapy <= 0 || mapx > w->mini_w ||
		mapx <= 0)))
		{
			w->cam->intersection.x = mapx;
			w->cam->intersection.y = mapy;
			return (1);
		}
	}
	return (0);
}
static inline int		intersection_hor(t_wolf3d *w, t_vec2f *dir)
{
	t_point			a;
	int				hit;
	t_point			offset;

	// printf("horstar\n");
	hit = 0;
	if (dir->y > 0)
	{
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE - 1;
		offset.y = -BLOC_SIZE;
	}
	else
	{
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		offset.y = BLOC_SIZE;
	}
	a.x = w->cam->position.x + (w->cam->position.y - a.y) / ttan(w->cam->fov);
	offset.x = 64 / ttan(w->cam->fov);
	while (hit == 0 && a.x / BLOC_SIZE < w->map->w && a.y / BLOC_SIZE < w->map->h)
	{
		if (a.x / BLOC_SIZE >= 0 && a.y / BLOC_SIZE >= 0 &&
			w->map->board[(int)a.y / BLOC_SIZE][(int)a.x / BLOC_SIZE])
		{
			// printf("a.x = %d, a.y = %d\n", a.x, a.y);
			w->cam->intersection_hor.x = a.x;
			w->cam->intersection_hor.y = a.y;
			w->cam->dist_hor = abs(w->cam->position.x - a.x) / tcos(w->cam->angle);
			hit = 1;
		}
		a.x = a.x + offset.x;
		a.y = a.y + offset.y;
	}
	// printf("horend\n");
	return (hit);
}
static inline int		intersection_ver(t_wolf3d *w, t_vec2f *dir)
{
	t_point			a;
	int				hit;
	t_point			offset;

	// printf("verstart\n");
	hit = 0;
	if (dir->x > 0)
	{
		a.x = floor(w->cam->position.x / BLOC_SIZE) * BLOC_SIZE - 1;
		offset.x = BLOC_SIZE;
	}
	else
	{
		a.x = floor(w->cam->position.x / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		offset.x = -BLOC_SIZE;
	}
	a.y = w->cam->position.y + (w->cam->position.x - a.x) * ttan(w->cam->fov);
	offset.y = 64 / ttan(w->cam->fov);
	while (hit == 0 && a.x / BLOC_SIZE < w->map->w && a.y / BLOC_SIZE < w->map->h)
	{
		//printf("a.x = %d, a.y = %d\n", a.x, a.y);
		if (a.x / BLOC_SIZE >= 0 && a.y / BLOC_SIZE >= 0 &&
			w->map->board[(int)a.y / BLOC_SIZE][(int)a.x / BLOC_SIZE])
		{
			//printf("a.x = %d, a.y = %d\n", a.x, a.y);
			w->cam->intersection_hor.x = a.x;
			w->cam->intersection_hor.y = a.y;
			w->cam->dist_ver = abs(w->cam->position.y - a.y) / tsin(w->cam->angle);
			hit = 1;
		}
		a.x = a.x + offset.x;
		a.y = a.y + offset.y;
	}
	// printf("verstend\n");
	return (hit);
}
