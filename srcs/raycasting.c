/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 09:48:05 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/22 14:21:08 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		render(t_wolf3d *w)
{
	int x;
	int y;
	int xpos;
	int ypos;
	int lineheight;

	x = -1;
	while (++x < WIN_W)
	{
		w->camerax = 2 * x / (double)(WIN_W) - 1;
		w->raydirx = w->xdir + w->xplane * w->camerax;
		w->raydiry = w->ydir + w->yplane * w->camerax;
		xpos = (int)w->posx;
		ypos = (int)w->posy;
		w->deltadistx = fabs(1 / w->raydirx);
		w->deltadisty = fabs(1 / w->raydiry);
		w->hit = 0;

		if (w->raydirx < 0)
		{
			w->stepx = -1;
			w->sidedistx = (w->posx - xpos) * w->deltadistx;
		}
		else
		{
			w->stepx = 1;
			w->sidedistx = (xpos + 1.0 - w->posx) * w->deltadistx;
		}

		if (w->raydiry < 0)
		{
			w->stepy = -1;
			w->sidedisty = (w->posy - ypos) * w->deltadisty;
		}
		else
		{
			w->stepy = 1;
			w->sidedisty = (ypos + 1.0 - w->posy) * w->deltadisty;
		}

		while (!w->hit)
		{
			if (w->sidedistx < w->sidedisty)
			{
				w->sidedistx += w->deltadistx;
				xpos += w->stepx;
				w->side = 0;
			}
			else
			{
				w->sidedisty += w->deltadisty;
				ypos += w->stepy;
				w->side = 1;
			}
			if (w->map->board[xpos][ypos] > 0)
				w->hit = 1;
		}
		if (!w->side)
			w->perpwalldist = (xpos - w->posx + (1 - w->stepx) / 2) / w->raydirx;
		else
			w->perpwalldist = (ypos - w->posy + (1 - w->stepy) / 2) / w->raydiry;
		lineheight = (int)(WIN_H / w->perpwalldist);
		int drawstart = -lineheight / 2 + WIN_H / 2;
		if (drawstart < 0) drawstart = 0;
		int drawend = lineheight / 2 + WIN_H / 2;
		if (drawend >= WIN_H) drawend = WIN_H - 1;
		y = drawstart;
		// printf("drawstart: %d\n", drawstart);
		// printf("drawend: %d\n", drawend);
		while (y < drawend)
		{
			// int d = y * 256 - WIN_H * 128 + lineheight * 128;
			// int color = LIGHTRED;
			// if (w->side == 1) color = (color >> 1) & 8355711;
				put_pixel_img(w, x, y, 0xFF0000);
			y++;
		}
	}
}
