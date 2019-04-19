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
static inline void 		inter_hor(t_wolf3d *w, int i, double angle)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	int 	j;
	double	v;
	int 	ac;

	j = 0;
	ac = (int)angle;
	if (ac > 180 && ac < 360)// ray is facing up
	{
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE - 1;
		o.y = -BLOC_SIZE;
	}
	else
	{
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		o.y = BLOC_SIZE;
	}
	if (ac == 90 || ac == 270)
	{
		v = 1;
		o.x = 0;
	}
	else if (ac == 180 || ac == 360)
	{
		v = 1;
		o.y = 0;
		o.x = BLOC_SIZE;
	}
	else
	{
		v = ttan(angle);
		o.x = BLOC_SIZE / v;
	}
	a.x = w->cam->position.x + (w->cam->position.y - a.y) / v;
	while (++j && a.x >= 0 && a.y >= 0 && a.x < w->mini_w && a.y < w->mini_h)
	{
		printf("%d intersection horizontal x = %f y = %f\n", j, a.x, a.y);
		if (w->map->board[(int)round(a.y / BLOC_SIZE)][(int)round(a.x / BLOC_SIZE)])
		{
			w->cam->inter[i][0] = (t_vec2f){.x = a.x, .y = a.y};
			printf("wall hit horizontal x = %f, y = %f\n", w->cam->inter[i][0].x, w->cam->inter[i][0].y);
			break;
		}
		a.x += ((ac > 180 && ac < 270) || (ac > 270 && ac < 360)) ? -o.x : o.x;
		a.y += o.y;
	}
}

static inline void 		inter_ver(t_wolf3d *w, int i, double angle)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	int j = 1;
	double	v;
	int 	ac;

	ac = (int)angle;
	if (ac > 90 && ac < 270) // ray is facing left
	{
		a.x = floor(w->cam->position.x / BLOC_SIZE) * BLOC_SIZE - 1;
		o.x = -BLOC_SIZE;
	}
	else
	{
		a.x = floor(w->cam->position.x / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		o.x = BLOC_SIZE;
	}
	if (ac == 90 || ac == 270)
	{
		v = 1;
		o.x = 0;
		o.y = BLOC_SIZE;
	}
	else if (ac == 180 || ac == 360)
	{
		v = 1;
		o.y = 0;
	}
	else
	{
		v = ttan(angle);
		o.y = BLOC_SIZE * v;
	}
	a.y = w->cam->position.y + (w->cam->position.x - a.x) * v;
	while (++j && a.x >= 0 && a.y >= 0 && a.x < w->mini_w && a.y < w->mini_h)
	{
		printf("%d intersection vertical x = %f y = %f\n", j, a.x, a.y);
		if (w->map->board[(int)round(a.y / BLOC_SIZE)][(int)round(a.x / BLOC_SIZE)])
		{
			w->cam->inter[i][1] = (t_vec2f){.x = a.x, .y = a.y};
			printf("wall hit vertical x = %f, y = %f\n", w->cam->inter[i][1].x, w->cam->inter[i][1].y);
			break;
		}
		a.y += ((ac > 180 && ac < 270) || (ac > 90 && ac < 180)) ? -o.y : o.y;
		a.x += o.x;
	}
}
// static inline int		fetch_color(t_wolf3d *w)
// {
// 	return (w->colors[(w->map->board[(int)w->cam->intersection.y / BLOC_SIZE]
// 									[(int)w->cam->intersection.x / BLOC_SIZE]) % 3]);
// }


/*static inline void		render(t_wolf3d *w, int i, double depth)
{
	int		h_seen;
	int		y;
	int		x;

	h_seen = CAM_DIST * WALL_H / depth;
	y = CAM_H - (h_seen / 2) - 1;
	x = -1;
	// while (++x < y + 151)
	// 	put_pixel_img(w, w->width - i + w->mini_w, x, 0x09e4ef);
	while (++y < (CAM_H + (h_seen / 2)))
		put_pixel_img(w, w->width - i + w->mini_w, y + 150, 0xff0000);
	// while (++y < w->width)
	// 	put_pixel_img(w, w->width - i + w->mini_w, y + 150, GREY);
}
*/
/*static inline void 		inter_hor(t_wolf3d *w, int i, double angle, double a_c)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	int 	j;

	j = 0;
	if (a_c >= 180 && a_c <= 360.0)// ray is facing up
	{
		printf("facing UP --- angle = %f\n", ttan(angle));
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		o.y = -BLOC_SIZE;
	}
	else
	{
		printf("facing DOWN --- angle = %f\n", ttan(angle));
		a.y = floor(w->cam->position.y / BLOC_SIZE) * BLOC_SIZE - 1;
		o.y = BLOC_SIZE;
	}
	a.x = w->cam->position.x + (w->cam->position.y - a.y) / ttan(angle);
	o.x = BLOC_SIZE / ttan(angle);
	while (++j && a.x >= 0 && a.y >= 0 && a.x < w->mini_w && a.y < w->mini_h)
	{
		printf("%d intersection horizontal x = %f y = %f\n", j, a.x, a.y);
		if (w->map->board[(int)a.y / BLOC_SIZE][(int)a.x / BLOC_SIZE])
		{
			w->cam->inter[i][0] = (t_vec2f){.x = a.x, .y = a.y};
			printf("wall hit horizontal x = %f, y = %f\n", w->cam->inter[i][0].x, w->cam->inter[i][0].y);
			break;
		}
		a.x += o.x;
		a.y += o.y;
	}
}

static inline void 		inter_ver(t_wolf3d *w, int i, double angle, double a_c)
{
	t_vec2f	a; // intersection point
	t_vec2f	o; // offset
	int j = 1;

	if (a_c >= 90.0 && a_c <= 270.0) // ray is facing left
	{
		printf("facing LEFT --- angle = %f\n", ttan(angle));
		a.x = floor(w->cam->position.x / BLOC_SIZE) * BLOC_SIZE - 1;
		o.x = -BLOC_SIZE;
	}
	else
	{
		printf("facing RIGHT --- angle = %f\n", ttan(angle));
		a.x = floor(w->cam->position.x / BLOC_SIZE) * BLOC_SIZE + BLOC_SIZE;
		o.x = BLOC_SIZE;
	}
	a.y = w->cam->position.y + (w->cam->position.x - a.x) * ttan(angle);
	o.y = BLOC_SIZE * ttan(angle);
	while (++j && a.x >= 0 && a.y >= 0 && a.x < w->mini_w && a.y < w->mini_h)
	{
		printf("%d intersection vertical x = %f y = %f\n", j, a.x, a.y);
		if (w->map->board[(int)a.y / BLOC_SIZE][(int)a.x / BLOC_SIZE])
		{
			w->cam->inter[i][1] = (t_vec2f){.x = a.x, .y = a.y};
			printf("wall hit vertical x = %f, y = %f\n", w->cam->inter[i][1].x, w->cam->inter[i][1].y);
			break;
		}
		a.y += o.y;
		a.x += o.x;
	}
}
*/

/*	t_vec2f		forward;
	t_vec2f		right;
	double		halfwidth;
	double		offset;*/

	i = -1;
	//printf("angle: %f\n", w->cam->angle);
/*	forward.x = tcos(w->cam->angle);
	forward.y = tsin(w->cam->angle);
	right.x = forward.y;
	right.y = -forward.x;
	halfwidth = ttan(w->cam->fov / 2.0);*/
	while (++i < limit && !(hit = 0))
	{
/*		offset = ((i * 2.0 / (limit - 1.0)) - 1.0) * halfwidth;
		dir.x = forward.x + offset * right.x;
		dir.y = forward.y + offset * right.y;*/
