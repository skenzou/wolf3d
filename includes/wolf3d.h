/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 09:40:39 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/22 10:41:00 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# define TNUM			32
# define WIN_W			1200
# define WIN_H			900
# define ESCAPE			53
# define UPARROW		126
# define DOWNARROW		125
# define RIGHTARROW		124
# define LEFTARROW		123
# define PLUS			69
# define MINUS			78
# define AKEY			0
# define SKEY			1
# define DKEY			2
# define QKEY			12
# define WKEY			13
# define SCROLLUP		5
# define SCROLLDOWN		4
# define SPACE			49
# define RKEY			15
# define MINIM_S		20
# define W_S			300
# define CAM_H			W_S / 2
# define ANSI_RED		"\x1b[1m\x1b[31m"
# define ANSI_GREEN		"\x1b[1m\x1b[32m"
# define ANSI_YELLOW	"\x1b[1m\x1b[33m"
# define ANSI_BLUE		"\x1b[1m\x1b[34m"
# define ANSI_MAGENTA	"\x1b[1m\x1b[35m"
# define ANSI_CYAN		"\x1b[1m\x1b[36m"
# define ANSI_RESET		"\x1b[1m\x1b[0m"
# define ANSI_BOLD		"\x1b[1m"
# define LIGHTRED		0xff0080
# define DARKBLUE		0x000099

typedef struct		s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
}					t_image;

typedef struct		s_point
{
	int x;
	int y;
	int color;
}					t_point;

typedef struct		s_map
{
	int				**board;
	int				w;
	int				h;
}					t_map;

typedef struct		s_wolf3d
{
	int				xpos;
	int				ypos;
	double			posx;
	double			posy;
	double			xdir;
	double			ydir;
	double			xplane;
	double			yplane;
	double			sidedistx;
	double			sidedisty;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	double			camerax;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			ang_s;
	t_image			*img;
	t_map			*map;
	void			*mlx_ptr;
	void			*win_ptr;
}					t_wolf3d;

t_map				*create_map(int fd);

void				create_image(t_wolf3d *w);
void				process(t_wolf3d *w);
int					put_pixel_img(t_wolf3d *w, int x, int y, int color);
void				draw_minimap(t_wolf3d *w);
void				put_line(t_wolf3d *w, t_point p1, t_point p2);

int					handle_mouse(int button, int x, int y, t_wolf3d *w);
int					handle_key(int keycode, t_wolf3d *w);
int					camera_mov(int x, int y, t_wolf3d *w);
void				render(t_wolf3d *w);

#endif
