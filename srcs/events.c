/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:23:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/19 10:54:30 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void		player_movement(int keycode, t_wolf3d *w)
{
	if (keycode == UPARROW)
		if (w->ypos > 0 && w->map->board[w->ypos - 1][w->xpos] == 0)
			w->ypos--;
	if (keycode == DOWNARROW)
		if (w->ypos < w->map->h - 1 && w->map->board[w->ypos + 1][w->xpos] == 0)
			w->ypos++;
	if (keycode == LEFTARROW)
		if (w->xpos > 0 && w->map->board[w->ypos][w->xpos - 1] == 0)
			w->xpos--;
	if (keycode == RIGHTARROW)
		if (w->xpos < w->map->w - 1 && w->map->board[w->ypos][w->xpos + 1] == 0)
			w->xpos++;
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
