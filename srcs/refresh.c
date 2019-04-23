/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 19:38:43 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/23 13:57:28 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void			launch_threads(t_wolf3d *w)
{
	pthread_attr_t	attr;
	int				err;
	int				i;

	i = 0;
	pthread_attr_init(&attr);
	while (i < TNUM)
	{
		err = pthread_create(&(w->tids[i]), &attr, raycasting,
															&w->tdata[i]);
		if (err)
		{
			perror("thread error");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < TNUM)
		pthread_join(w->tids[i++], NULL);
}

static int			display_menu(t_wolf3d *w)
{
	if (!w->options)
		mlx_put_image_to_window(w->mlx_ptr, w->win_ptr,
												w->textures[5]->ptr, 0, 0);
	else
		mlx_put_image_to_window(w->mlx_ptr, w->win_ptr,
											w->textures[6]->ptr, 0, 0);
	return (0);
}

int					refresh(t_wolf3d *w)
{
	if (w->sleep && !(w->sleep = 0))
		sleep(2);
	display_menu(w);
	if (w->menu)
		return (display_menu(w));
	if (w->scary)
	{
		w->time++;
		if (w->time % 1800 == 0)
		{
			mlx_put_image_to_window(w->mlx_ptr, w->win_ptr,
													w->textures[7]->ptr, 0, 0);
			w->sleep = 1;
			return (0);
		}
	}
	launch_threads(w);
	draw_mmap(w, 0, 0);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->img->ptr, 0, 0);
	if (!w->scary)
		mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->minimap->ptr, 0, 0);
	return (0);
}
