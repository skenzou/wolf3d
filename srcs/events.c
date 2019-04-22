/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:23:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/22 16:01:05 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static inline void		player_movement(int keycode, t_wolf3d *w)
{
	if (w->menu)
		return ;
	if (keycode == UPARROW || keycode == WKEY)
		w->cam->position = collision(w, w->cam->position, (t_vec2f){
		.x = w->cam->position.x + tcos(w->cam->angle) * w->cam->speedmove,
		.y = w->cam->position.y - tsin(w->cam->angle) * w->cam->speedmove});
	if (keycode == DOWNARROW || keycode == SKEY)
		w->cam->position = collision(w, w->cam->position, (t_vec2f){
		.x = w->cam->position.x - tcos(w->cam->angle) * w->cam->speedmove,
		.y = w->cam->position.y + tsin(w->cam->angle) * w->cam->speedmove});
	if (keycode == 0)
		w->cam->position = collision(w, w->cam->position, (t_vec2f){
		.x = w->cam->position.x - tsin(w->cam->angle) * w->cam->speedmove,
		.y = w->cam->position.y - tcos(w->cam->angle) * w->cam->speedmove});
	if (keycode == 2)
		w->cam->position = collision(w, w->cam->position, (t_vec2f){
		.x = w->cam->position.x + tsin(w->cam->angle) * w->cam->speedmove,
		.y = w->cam->position.y + tcos(w->cam->angle) * w->cam->speedmove});
	(keycode == RIGHTARROW) && (w->cam->angle -= w->cam->speedangle);
	(keycode == LEFTARROW) && (w->cam->angle += w->cam->speedangle);
	(w->cam->angle > 360) && (w->cam->angle = 0);
	(w->cam->angle < 0) && (w->cam->angle = 360);
}

int						menu_event(int b, int x, int y, t_wolf3d *w)
{
	if (b != 1 || !w->menu)
		return (0);
	if (x > 288 && x < 776 && y > 462 && y < 535)
	{
		w->menu = 0;
		CGDisplayHideCursor(kCGDirectMainDisplay);
	}
	if (x > 289 && x < 780 && y > 592 && y < 666)
		exit(1);
	return (1);
}

int						camera_mov(int x, int y, t_wolf3d *w)
{
	int32_t deltax;
	int32_t deltay;

	(void)x;
	(void)y;
	CGGetLastMouseDelta(&deltax, &deltay);
	if (w->menu)
		return (1);
	if (deltax > 0)
		w->cam->angle -= ((float)deltax / 32) * w->cam->speedangle;
	if (deltax < 0)
		w->cam->angle += ((float)deltax / -32) * w->cam->speedangle;
	if (deltay > 0 && w->cam->height > 15)
		w->cam->height -= ((float)deltay / 32) * 100;
	if (deltay < 0 && w->cam->height < 800)
		w->cam->height += ((float)deltay / -32) * 100;
	while (w->cam->angle > 360)
		w->cam->angle -= 360;
	while (w->cam->angle < 0)
		w->cam->angle += 360;
	return (1);
}

int						key_pressed(int keycode, t_wolf3d *w)
{
	keycode == ESCAPE ? exit(0) : 0;
	if (keycode == 48)
	{
		w->menu = !w->menu;
		if (w->menu)
			CGDisplayShowCursor(kCGDirectMainDisplay);
		else
			CGDisplayHideCursor(kCGDirectMainDisplay);
	}
	if (!w->menu)
		player_movement(keycode, w);
	return (1);
}
