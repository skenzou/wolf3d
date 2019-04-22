/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 09:45:23 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/22 20:38:11 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		check_error(int argc)
{
	if (argc != 2)
	{
		ft_putendl_fd(ANSI_RED "usage: ./wolf3d <map>", 2);
		exit(1);
	}
}

int				main(int argc, char **argv)
{
	t_wolf3d	w;
	int			fd;

	check_error(argc);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("error");
		return (0);
	}
	init_wolf3d(fd, &w);
	mlx_loop(w.mlx_ptr);
	return (0);
}
