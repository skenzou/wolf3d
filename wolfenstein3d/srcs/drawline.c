/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:30:33 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/18 15:21:30 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		put_hor(t_wolf3d *w, t_point p1, t_point p2, t_point d)
{
	int		j;
	int		var;
	t_point i;
	t_point curr;

	curr = (t_point){.x = p1.x, .y = p1.y, .color = p1.color};
	i = (t_point){.x = p2.x - p1.x > 0 ? 1 : -1, .y = p2.y - p1.y > 0 ? 1 : -1};
	j = 1;
	var = (d.x > d.y ? d.x : d.y) / 2;
	while (j++ <= d.x && (var += d.y))
	{
		curr.x += i.x;
		(var >= d.x) && (curr.y += i.y);
		(var >= d.x) && (var -= d.x);
		put_pixel_img(w, curr.x, curr.y, curr.color);
	}
}

static void		put_ver(t_wolf3d *w, t_point p1, t_point p2, t_point d)
{
	int		j;
	int		var;
	t_point i;
	t_point curr;

	curr = (t_point){.x = p1.x, .y = p1.y, .color = p1.color};
	i = (t_point){.x = p2.x - p1.x > 0 ? 1 : -1, .y = p2.y - p1.y > 0 ? 1 : -1};
	j = 1;
	var = (d.x > d.y ? d.x : d.y) / 2;
	while (j++ <= d.y && (var += d.x))
	{
		curr.y += i.y;
		(var >= d.y) && (curr.x += i.x);
		(var >= d.y) && (var -= d.y);
		put_pixel_img(w, curr.x, curr.y, curr.color);
	}
}

void			put_line(t_wolf3d *w, t_point p1, t_point p2)
{
	t_point d;

	d = (t_point){.x = p2.x - p1.x, .y = p2.y - p1.y};
	d = (t_point){.x = abs(d.x), .y = abs(d.y)};
	put_pixel_img(w, p1.x, p1.y, p1.color);
	if (d.x > d.y)
		put_hor(w, p1, p2, d);
	else
		put_ver(w, p1, p2, d);
}