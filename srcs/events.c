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
	double oldxdir;
	double oldplanex;

	if (keycode == UPARROW)
	{
		if (w->map->board[(int)(w->posx + w->xdir)][(int)w->posy] == 0)
			w->posx += w->xdir;
		if (w->map->board[(int)w->posx][(int)(w->posy + w->ydir)] == 0)
			w->posy += w->ydir;
	}
	if (keycode == DOWNARROW)
	{
		if (w->map->board[(int)(w->posx - w->xdir)][(int)w->posy] == 0)
			w->posx -= w->xdir;
		if (w->map->board[(int)w->posx][(int)(w->posy - w->ydir)] == 0)
			w->posy -= w->ydir;
	}
	if (keycode == LEFTARROW)
	{
		oldxdir = w->xdir;
		w->xdir = w->xdir * cos(0.07) - w->ydir * sin(0.07);
		w->ydir = oldxdir * sin(0.07) + w->ydir * cos(0.07);
		oldplanex = w->xplane;
		w->xplane = w->xplane * cos(0.07) - w->yplane * sin(0.07);
		w->yplane = oldplanex * sin(0.07) + w->yplane * cos(0.07);
	}
	if (keycode == RIGHTARROW)
	{
		oldxdir = w->xdir;
		w->xdir = w->xdir * cos(-0.07) - w->ydir * sin(-0.07);
		w->ydir = oldxdir * sin(-0.07) + w->ydir * cos(-0.07);
		oldplanex = w->xplane;
		w->xplane = w->xplane * cos(-0.07) - w->yplane * sin(-0.07);
		w->yplane = oldplanex * sin(-0.07) + w->yplane * cos(-0.07);
	}
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
