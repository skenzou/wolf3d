/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:23:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/18 13:09:07 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void		backward(t_wolf3d *w)
{
	int nextx;
	int nexty;

	nextx = w->cam->position.x - tcos(w->cam->angle) * w->cam->speedmove;
	nexty = w->cam->position.y + tsin(w->cam->angle) * w->cam->speedmove;
	if (nexty / BLOC_SIZE < w->map->h && nextx / BLOC_SIZE < w->map->w &&
		nexty >= 0 && nextx >= 0
					&& w->map->board[nexty / BLOC_SIZE][nextx / BLOC_SIZE] == 0)
	{
		// printf(" -----Backward----Next position of the player : x = %d, y = %d\n", nextx, nexty);
		w->cam->position.x = nextx;
		w->cam->position.y = nexty;
	}
}

static inline void		forward(t_wolf3d *w)
{
	int nextx;
	int nexty;

	nextx = w->cam->position.x + tcos(w->cam->angle) * w->cam->speedmove;
	nexty = w->cam->position.y - tsin(w->cam->angle) * w->cam->speedmove;
	if (nexty / BLOC_SIZE < w->map->h && nextx / BLOC_SIZE < w->map->w &&
		nexty >= 0 && nextx >= 0
					&& w->map->board[nexty / BLOC_SIZE][nextx / BLOC_SIZE] == 0)
	{
		// printf("------Forward----Next position of the player : x = %d, y = %d\n", nextx, nexty);
		w->cam->position.x = nextx;
		w->cam->position.y = nexty;
	}
}

static inline void 		left(t_wolf3d *w)
{
	int	nextx;
	int	nexty;

	nextx = w->cam->position.x + tsin(w->cam->angle) * w->cam->speedmove;
	nexty = w->cam->position.y + tcos(w->cam->angle) * w->cam->speedmove;
	if (nexty / BLOC_SIZE < w->map->h && nextx / BLOC_SIZE < w->map->w &&
		nexty >= 0 && nextx >= 0
					&& w->map->board[nexty / BLOC_SIZE][nextx / BLOC_SIZE] == 0)
	{
		w->cam->position.x = nextx;
		w->cam->position.y = nexty;
	}
}

static inline void 		right(t_wolf3d *w)
{
	int	nextx;
	int	nexty;

	nextx = w->cam->position.x - tsin(w->cam->angle) * w->cam->speedmove;
	nexty = w->cam->position.y - tcos(w->cam->angle) * w->cam->speedmove;
	if (nexty / BLOC_SIZE < w->map->h && nextx / BLOC_SIZE < w->map->w &&
		nexty >= 0 && nextx >= 0
					&& w->map->board[nexty / BLOC_SIZE][nextx / BLOC_SIZE] == 0)
	{
		w->cam->position.x = nextx;
		w->cam->position.y = nexty;
	}
}

static inline void		player_movement(int keycode, t_wolf3d *w)
{
	if (keycode == UPARROW)
		forward(w);
	if (keycode == DOWNARROW)
		backward(w);
	if (keycode == 0)
		right(w);
	if (keycode == 2)
		left(w);
	(keycode == RIGHTARROW) && (w->cam->angle -= w->cam->speedangle);
	(keycode == LEFTARROW) && (w->cam->angle += w->cam->speedangle);
	(keycode == SPACE) && (w->texture = w->texture == 0 ? 1 : 0);
	(w->cam->angle > 360) && (w->cam->angle = 0);
	(w->cam->angle < 0) && (w->cam->angle = 360);
}

int						camera_mov(int x, int y, t_wolf3d *w)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		w->cam->angle = atan2((double)x, (double) y);
		w->cam->angle *= -3;
		w->cam->angle *= 180 / M_PI;
		while (w->cam->angle > 360)
			w->cam->angle -= 360;
		while (w->cam->angle < 0)
			w->cam->angle += 360;
		process(w);
	}

		// if (x > w->width / 2)
		// 	w->cam->angle -= ((double)x / (w->width / 2)) * angle;
		// else
		// 	w->cam->angle += ((double)x / (w->width / 2)) * angle;
		// (w->cam->angle > 360) && (w->cam->angle = 0);
		// (w->cam->angle < 0) && (w->cam->angle = 360);
	return (1);
}

int						handle_key(int keycode, t_wolf3d *w)
{
	player_movement(keycode, w);
	keycode == ESCAPE ? exit(0) : 0;
	process(w);
	return (1);
}

int						handle_mouse(int button, int x, int y, t_wolf3d *w)
{
	(void)x;
	(void)y;
	(void)button;
	(void)w;
	return (1);
}
