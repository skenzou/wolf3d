/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 09:40:39 by midrissi          #+#    #+#             */
/*   Updated: 2019/04/23 12:21:28 by midrissi         ###   ########.fr       */
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
# include <ApplicationServices/ApplicationServices.h>
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
# define BLOC_SIZE		64
# define WIDTH			1024
# define HEIGHT			768
# define WALL_H			WIDTH
# define NORTH			0
# define SOUTH			1
# define EAST			2
# define WEST			3
# define CAM_DIST		50.0
# define ORANGE			0xaf4e11
# define PURPLE			0x751b91
# define BLUE			0x081ae0
# define GREY			0x687272
# define RED			0xff0000

typedef struct		s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
	int			height;
	int			width;
	int			test;
}					t_image;

typedef struct		s_point
{
	int				x;
	int				y;
	int				color;
}					t_point;

typedef struct		s_vec2f
{
	double			x;
	double			y;
	int				color;
}					t_vec2f;

typedef struct		s_camera
{
	double			pangle;
	double			radius;
	double			angle;
	double			fov;
	double			speedmove;
	double			speedangle;
	int				height;
	t_vec2f			intersection;
	t_vec2f			position;
	t_vec2f			interv[WIDTH];
	t_vec2f			interh[WIDTH];
	t_vec2f			rays[WIDTH];
}					t_camera;

typedef struct		s_map
{
	int				**board;
	int				w;
	int				h;
}					t_map;

typedef struct		s_thread_data
{
	int				y;
	int				x;
	int				y_end;
	int				x_end;
	char			inter;
	int				direction;
	int				i;
	struct s_wolf3d	*w;
}					t_thread_data;

typedef struct		s_wolf3d
{
	t_map			*map;
	t_camera		*cam;
	int				hit;
	t_image			*img;
	void			*mlx_ptr;
	void			*win_ptr;
	t_image			*textures[8];
	int				mini_h;
	int				mini_w;
	int				width;
	int				height;
	t_image			*minimap;
	char			inter;
	int				direction;
	double			cos_table[WIDTH];
	double			tan_table[WIDTH];
	t_thread_data	tdata[TNUM];
	pthread_t		tids[TNUM];
	char			menu;
	char			nightmode;
	unsigned long	time;
	unsigned long	limit;
	char			scary;
	char			sleep;
	char			options;
	int				texturelight;
	double			floorlight;
}					t_wolf3d;

/*
** READ.C
*/
t_map				*create_map(int fd);
/*
** INIT.C
*/
void				init_wolf3d(int fd, t_wolf3d *w);
/*
** REFRESH.C
*/
int					refresh(t_wolf3d *w);
/*
** COLLISION.C
*/
t_vec2f				collision(t_wolf3d *w, t_vec2f old, t_vec2f new);
/*
** MINIMAP.C
*/
void				draw_mmap(t_wolf3d *w, int yoffset, int xoffset);
/*
** RAYCASTING.C
*/
void				*raycasting(void *data);
void				render(double depth, t_thread_data *d, double angle);
/*
** INTERSECTION.C
*/
void				inter_ver(t_thread_data *d, double angle);
void				inter_hor(t_thread_data *d, double angle);
/*
** EVENTS.C
*/
int					key_pressed(int keycode, t_wolf3d *w);
int					camera_mov(int x, int y, t_wolf3d *w);
int					menu_event(int b, int x, int y, t_wolf3d *w);
int					close_click(t_wolf3d *w);
/*
** IMAGE.C
*/
t_image				*create_image(t_wolf3d *w, char *path, int width,
																	int height);
int					put_pixel_img(t_image *img, int x, int y, int color);
/*
** UTILS.C
*/
double				tcos(double angle);
double				tsin(double angle);
double				ttan(double angle);
void				end(char *str, int fd);
/*
** UTILS2.C
*/
void				cos_lookuptable(t_wolf3d *w, t_thread_data *d);
void				tan_lookuptable(t_wolf3d *w, t_thread_data *d);

#endif
