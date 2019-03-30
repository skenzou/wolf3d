/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkamegne <rkamegne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 19:10:24 by rkamegne          #+#    #+#             */
/*   Updated: 2019/03/30 12:53:00 by rkamegne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

// void 	projection3D(t_wolf3d *w)
// {
//
// 	int 		i;
// 	double		wall_h;
// 	double		perpdistwall;
// 	double		dist_w;
// 	double		dist_c;
// 	double		cam_h;
// 	double		h_seen;
// 	int 		y;
// 	int			hit;
//
// 	//t_point		dir;
//
// 	wall_h = 1000.0;
// 	cam_h = 500.0;
// 	dist_c = 50.0;
// 	//perpdistwall = WIN_W / tTan(30.0);
// 	i = -1;
// 	while (++i < WIN_W)
// 	{
// 		w->cam->rays[i].startPoint = w->cam->position;
// 		w->cam->rays[i].startPoint.color = 0xff0000;
// 		w->cam->rays[i].endPoint.color = 0xff0000;
//
// 		if ((hit = intersection(w, i, 0)))
// 			w->cam->rays[i].endPoint = w->cam->intersection;
// 		else
// 		{
// 			w->cam->rays[i].endPoint.x = w->cam->position.x + w->cam->raylength * tCos((w->cam->angle + w->cam->fov / 2) - (i * (w->cam->fov / WIN_W)));
// 			w->cam->rays[i].endPoint.y = w->cam->position.y + w->cam->raylength * tSin((w->cam->angle + w->cam->fov / 2) - (i * (w->cam->fov / WIN_W)));
// 		}
// 		perpdistwall = sqrt(pow((w->cam->position.x - w->cam->rays[i].endPoint.x), 2) + pow((w->cam->position.y - w->cam->rays[i].endPoint.y), 2));
// 		dist_w =  perpdistwall * tCos(30.0);
// 		h_seen = dist_c * wall_h / dist_w;
// 		y = cam_h - (h_seen / 2) - 1;
// 		if (hit == 1)
// 			while (++y < (cam_h + (h_seen / 2)))
// 				put_pixel_img(w, i + WIDTH_MM, y + 250, 0xff0000);
// 	}
// }
