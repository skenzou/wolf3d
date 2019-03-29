/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:23:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/22 13:06:51 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void		player_movement(int keycode, t_wolf3d *w)
{
	int nextx;
	int nexty;

	if (keycode == UPARROW)
	{
		nextx = w->cam->position.x + Cos(w->cam->angle) * w->cam->speedmove;
		nexty = w->cam->position.y + Sin(w->cam->angle) * w->cam->speedmove;
		if (nexty / BLOC_SIZE < w->map->h && w->map->board[nexty / BLOC_SIZE][nextx / BLOC_SIZE] == 0)
		{
			w->cam->position.x = nextx;
			w->cam->position.y = nexty;
		}
	}
	if (keycode == DOWNARROW)
	{
		nextx = w->cam->position.x - Cos(w->cam->angle) * w->cam->speedmove;
		nexty = w->cam->position.y - Sin(w->cam->angle) * w->cam->speedmove;
		if (nexty / BLOC_SIZE < w->map->h && w->map->board[nexty / BLOC_SIZE][nextx / BLOC_SIZE] == 0)
		{
			w->cam->position.x = nextx;
			w->cam->position.y = nexty;
		}
	}
	if (keycode == LEFTARROW)
		w->cam->angle -= w->cam->speedangle;
	if (keycode ==  RIGHTARROW)
		w->cam->angle += w->cam->speedangle;
	if (w->cam->angle > 360)
		w->cam->angle = 0;
	if (w->cam->angle < 0)
		w->cam->angle = 360;
}

int						handle_key(int keycode, t_wolf3d *w)
{
	player_movement(keycode, w);
	keycode == ESCAPE ? exit(0) : 0;
	(void)w;
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
