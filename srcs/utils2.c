/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 19:34:33 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/23 13:54:27 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			cos_lookuptable(t_wolf3d *w, t_thread_data *d)
{
	int			i;
	double		angle;

	i = d->x;
	while (i < d->x_end)
	{
		angle = (w->cam->fov / 2) - (i * w->cam->fov / w->width);
		w->cos_table[i++] = tcos(angle);
	}
}

void			tan_lookuptable(t_wolf3d *w, t_thread_data *d)
{
	int			i;
	double		angle;

	i = d->x;
	while (i < d->x_end)
	{
		angle = w->cam->angle + (w->cam->fov / 2) -
												(i * w->cam->fov / w->width);
		w->tan_table[i++] = ttan(angle);
	}
}

int				close_click(t_wolf3d *w)
{
	(void)w;
	exit(0);
	return (0);
}
