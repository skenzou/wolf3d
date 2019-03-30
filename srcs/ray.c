#include "wolf3d.h"

void	draw_wall(t_wolf3d *w, int dist, int x)
{
	//dist = distance between the ray and the wall encountered
	int 	draw_s;
	int		draw_e;
	int		y;

	 draw_s = 25 - (50 * dist / 277);
	// printf("draw_s = %d\n", draw_s);
	 if (draw_s < 0)
	 	draw_s = 0;
	 draw_e = 25 + (50 * dist / 277);
	// printf("draw_e = %d\n", draw_e);
	 if (draw_e >= W_M)
	 	draw_e = W_M - 1;
	 y = draw_s;
	 while (y++ <= draw_e)
	 	put_pixel_img(w, x, y, 0xff0000);
}

/*void	ray_cast(t_wolf3d *w)
{
	int 		wall_hit;
	t_vector	ray; //ray x and ray y will define the ray vector
	double		angle_s;
	int 		i;

	angle_s = 0.0;
	wall_hit = 0; // wall_hit = 1 if a ray meets a wall
	while (wall_hit == 0 && angle_s <= FOV)
	{
		i = -1;
		while (++i <= W_M)
		{
			printf("dist = %d\n angle_s = %f\n", i ,angle_s);
			ray.x = w->posx + i * cos(angle_s * M_PI / 180.0);
			ray.y = w->posy + i * sin(angle_s * M_PI / 180.0);
			//printf("ray.x = %f and ray.y = %f\n", cos(angle_s), sin(angle_s));
			printf("ray.x = %d and ray.y = %d\n", ray.x / MINIM_S, ray.y / MINIM_S);
			if (ray.x > 0 && ray.y > 0 && ray.x < W_M / MINIM_S && ray.y < H_M / MINIM_S
				&& w->map->board[ray.y / MINIM_S][ray.x / MINIM_S] != 0)
			{				
				wall_hit = 1;
				break;
			}
		}
		angle_s += 60.0 / W_M;
	}
	if (wall_hit == 1)
		draw_wall(w, i);
}
*/
void	ray_cast(t_wolf3d *w)
{
	int			wall_hit; // tell us if a ray hits a wall so we can stop the algorithm
	t_ray		ray;	// add the ray if we don't hit a wall
	double		angle_s; // will be a part of the FOV (subsequent column)
	int			rayAdvance = 0;

	int			x; // for each pixels ont the screen

	angle_s = 0.0;
	x = -1;
	while (++x < 2)
	{
		while (angle_s < FOV / 2) // cast rays
		{
			rayAdvance = 0;
			while (++rayAdvance <= (277 / cos(angle_s * M_PI / 180.0)))
			{
				ray.x = w->posx + rayAdvance * cos(angle_s * M_PI / 180.0);
				ray.y = w->posy + rayAdvance * sin(angle_s * M_PI / 180.0);
				//printf("angle = %f\n", angle_s);
				//printf("ray.x = %f, ray.y = %f\n, rayAdvance = %d\n", ray.x, ray.y, rayAdvance);
				if (ray.x < w->map->h && ray.y < w->map->h && w->map->board[(int)ray.y][(int)ray.x] != 0)
				{
					printf("ray.x = %f, ray.y = %f\n, rayAdvance = %d\n", ray.x, ray.y, rayAdvance);
					wall_hit = 1;
					break;
				}
			}
			//printf("wall_hit = %d\n", wall_hit);
			if (wall_hit == 1)
				draw_wall(w, rayAdvance, x);
			angle_s += 30.0 / W_M;
			//printf("angle111 = %f\n", angle_s);
		}
	}
}