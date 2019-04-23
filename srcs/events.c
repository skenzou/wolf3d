/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 15:23:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/23 13:55:56 by midrissi         ###   ########.fr       */
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

static void				options_tab(int x, int y, t_wolf3d *w)
{
	if (x > 286 && x < 763 && y > 313 && y < 387)
	{
		w->scary = 0;
		w->nightmode = 1;
		w->texturelight = 50;
		w->floorlight = 100.;
	}
	if (x > 286 && x < 763 && y > 412 && y < 482)
	{
		w->nightmode = 0;
		w->scary = 0;
	}
	if (x > 286 && x < 763 && y > 513 && y < 584)
	{
		w->time = 0;
		w->scary = 1;
		w->nightmode = 1;
		w->texturelight = 5;
		w->floorlight = 20.;
	}
	if (x > 34 && x < 206 && y > 671 && y < 715)
		w->options = 0;
}

int						menu_event(int b, int x, int y, t_wolf3d *w)
{
	if (b != 1 || !w->menu)
		return (0);
	if (!w->options)
	{
		if (x > 280 && x < 770 && y > 321 && y < 398)
		{
			w->menu = 0;
			CGDisplayHideCursor(kCGDirectMainDisplay);
		}
		if (x > 280 && x < 770 && y > 423 && y < 501)
		{
			w->options = 1;
			return (1);
		}
		if (x > 280 && x < 770 && y > 523 && y < 600)
			exit(1);
	}
	else
		options_tab(x, y, w);
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
		w->options = 0;
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
