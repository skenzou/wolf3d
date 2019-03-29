/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 09:40:39 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/25 16:15:32 by rkamegne         ###   ########.fr       */
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
# define MINIM_S		64
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
# define FOV			60
# define H_M 			200
# define W_M 			320
# define X_BLOC			20
# define Y_BLOC			16
# define BLOC_SIZE		32
# define WIDTH			(X_BLOC * BLOC_SIZE)
# define HEIGHT			(Y_BLOC * BLOC_SIZE)

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
	int				x;
	int				y;
	int				color;
}					t_point;

typedef struct  	s_vector2f
{
		t_point		startPoint;
		t_point		endPoint;
}					t_vector2f;
typedef struct 		s_vec2f
{
	float			x;
	float			y;
}					t_vec2f;
typedef struct 		s_camera
{
	float			radius;
	float			angle;
	float			fov;
	float			raylength;
	float			speedmove;
	float			speedangle;
	t_point			position;
	t_point			intersection;
	t_vector2f		rays[WIDTH];
}					t_camera;

typedef	struct 		s_map
{
	int				**board;
	int				w;
	int				h;
}					t_map;

typedef struct		s_wolf3d
{
	t_map			*map;
	t_camera		*cam;
	int				hit;
	t_image			*img;
	void			*mlx_ptr;
	void			*win_ptr;
}					t_wolf3d;

void				create_image(t_wolf3d *w);
int					put_pixel_img(t_wolf3d *w, int x, int y, int color);
void				put_line(t_wolf3d *w, t_point p1, t_point p2);

int					handle_mouse(int button, int x, int y, t_wolf3d *w);
int					handle_key(int keycode, t_wolf3d *w);
float				Cos(float angle);
float				Sin(float angle);
void				draw_mmap(t_wolf3d *w);
t_map				*create_map(int fd);
void				process(t_wolf3d *w);
t_camera			*camera_init(void);
int 				intersection(t_wolf3d *w, int iteration);
#endif
