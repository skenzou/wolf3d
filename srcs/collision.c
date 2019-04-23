/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 19:48:37 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/23 13:34:55 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		top_l(t_vec2f *new, t_point *block)
{
	double dx;
	double dy;

	dx = new->x - block->x * 64;
	dy = new->y - block->y * 64;
	if ((dx * dx + dy * dy) < 400)
	{
		if (dx * dx > dy * dy)
			new->x = block->x * 64 + 20;
		else
			new->y = block->y * 64 + 20;
	}
	return (1);
}

static int		top_r(t_vec2f *new, t_point *block)
{
	double dx;
	double dy;

	dx = new->x - (block->x + 1) * 64;
	dy = new->y - block->y * 64;
	if ((dx * dx + dy * dy) < 400)
	{
		if (dx * dx > dy * dy)
			new->x = (block->x + 1) * 64 - 20;
		else
			new->y = block->y * 64 + 20;
	}
	return (1);
}

static int		bot_l(t_vec2f *new, t_point *block)
{
	double dx;
	double dy;

	dx = new->x - block->x * 64;
	dy = new->y - (block->y + 1) * 64;
	if ((dx * dx + dy * dy) < 400)
	{
		if (dx * dx > dy * dy)
			new->x = block->x * 64 + 20;
		else
			new->y = (block->y + 1) * 64 - 20;
	}
	return (1);
}

static int		bot_r(t_vec2f *new, t_point *block)
{
	double dx;
	double dy;

	dx = new->x - (block->x + 1) * 64;
	dy = new->y - (block->y + 1) * 64;
	if ((dx * dx + dy * dy) < 400)
	{
		if (dx * dx > dy * dy)
			new->x = (block->x + 1) * 64 - 20;
		else
			new->y = (block->y + 1) * 64 - 20;
	}
	return (1);
}

#define TOP		0
#define BOT		1
#define LEFT	2
#define RIGHT	3

t_vec2f			collision(t_wolf3d *w, t_vec2f old, t_vec2f new)
{
	t_point		b;
	int			d[4];

	b = (t_point){.x = floor(new.x) / 64, .y = floor(new.y) / 64};
	if ((int)floor(new.y) / BLOC_SIZE >= w->map->h ||
		(int)floor(new.x) / BLOC_SIZE >= w->map->w || new.y < 0 || new.x < 0
		|| w->map->board[b.y][b.x])
		return (old);
	d[TOP] = w->map->board[b.y - 1][b.x];
	d[BOT] = w->map->board[b.y + 1][b.x];
	d[LEFT] = w->map->board[b.y][b.x - 1];
	d[RIGHT] = w->map->board[b.y][b.x + 1];
	if (d[TOP] && new.y - b.y * 64 < 20)
		new.y = b.y * 64 + 20;
	if (d[BOT] && (b.y + 1) * 64 - new.y < 20)
		new.y = (b.y + 1) * 64 - 20;
	if (d[LEFT] && new.x - b.x * 64 < 20)
		new.x = b.x * 64 + 20;
	if (d[RIGHT] && (b.x + 1) * 64 - new.x < 20)
		new.x = (b.x + 1) * 64 - 20;
	w->map->board[b.y - 1][b.x - 1] && !(d[TOP] && d[LEFT]) && top_l(&new, &b);
	w->map->board[b.y - 1][b.x + 1] && !(d[TOP] && d[RIGHT]) && top_r(&new, &b);
	w->map->board[b.y + 1][b.x - 1] && !(d[BOT] && d[LEFT]) && bot_l(&new, &b);
	w->map->board[b.y + 1][b.x + 1] && !(d[BOT] && d[RIGHT]) && bot_r(&new, &b);
	return (new);
}
