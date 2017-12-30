/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 18:40:17 by mikim             #+#    #+#             */
/*   Updated: 2017/12/29 23:26:46 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <pthread.h>

# define WID_MAX 1900
# define WID_MIN 100
# define HGT_MAX 1200
# define HGT_MIN 100

# define THREAD 16
# define PALETTE 16
# define RED 65536
# define GREEN 256
# define BLUE 1
# define WHITE 0xFFFFFF

# define WID_RATE 100
# define HGT_RATE 100
# define ZOOM_RATE 1.1
# define MOVE_RATE 0.05

# define KEY 2
# define MOUSE 4
# define MOTION 6
# define EXPOSE 12

# define MOVE_LEFT 0
# define MOVE_UP 1
# define MOVE_RIGHT 2
# define MOVE_DOWN 13
# define ZOOM_AUTO 6
# define COLOR 8
# define RESET 15
# define ZOOM_IN 30
# define ZOOM_OUT 33
# define MOTION_LOCK 49
# define ESC 53
# define WID_DN 123
# define WID_UP 124
# define HGT_DN 125
# define HGT_UP 126

# define LEFT 1
# define RIGHT 2
# define WHEEL_UP 4
# define WHEEL_DN 5

# define ITER_UP(x) (x == 24 || x == 69)
# define ITER_DN(x) (x == 27 || x == 78)
# define CHANGE(x) ((x >= 18 && x <= 23) || (x >= 83 && x <= 87))
# define MOVE(x) ((x >= 0 && x <= 2) || x == 13)
# define ZOOM(x) (x == 30 || x == 33)
# define SIZE(x) (x >= 123 && x <= 126)

# define MANDELBROT(x) (x == 18 || x == 83)
# define JULIA(x) (x == 19 || x == 84)
# define P_TREE(x) (x == 20 || x == 85)
# define BBB(x) (x == 21 || x == 86)
# define CCC(x) (x == 23 || x == 87)

typedef	enum		e_fractol
{
	mandel = 1,
	jul = 2,
	pt = 3,
	bbbb = 4,
	cccc = 5
}					t_fractol;

typedef	struct		s_env
{
	void			*mlx;
	void			*win;
	char			*img;
	int				*data;
	int				wid;
	int				hgt;
	int				bits;
	int				size;
	int				endian;
	t_fractol		frac;
	pthread_mutex_t	mutex;
	int				max;
	int				div;
	int				*palette;
	int				color;
	int				color_set;
	long double		x_fix;
	long double		y_fix;
	long double		zoom;
	int				zoom_auto;
	int				motion;
	int				expose;
}					t_env;

typedef struct		s_thread
{
	t_env			*e;
	int				n;
	int				thread;
}					t_thread;

/*
**					fractol
*/

void				fractol(t_env *e);
void				*plot(void *arg);
void				cross_hair(t_env *e);

/*
**					parse_handler
*/

void				parse(t_env *e);
void				init(t_env *e);
void				init_mlx(t_env *e);
void				init_color(t_env *e);

/*
**					mandelbrot
*/

void				mandelbrot(t_env *e, int thread, int n);
int					mandelbrot_iter(t_env *e, long double x, long double y);

/*
**					color_handler
*/

void				init_color(t_env *e);
void				color_blue(t_env *e);
void				color_green(t_env *e);
void				color_red(t_env *e);
void				color_custom(t_env *e);

/*
**					hook_handler
*/

int					key_hooks(int code, t_env *e);
int					mouse_hooks(int button, int x, int y, t_env *e);
int					motion_hooks(int x, int y, t_env *e);
int					expose_hooks(t_env *e);

/*
**					key_handler
*/

void				change(t_env *e, int code);
void				move(t_env *e, int code);
void				zoom(t_env *e, int code);
void				size(t_env *e, int code);
void				reset(t_env *e);

/*
**					exit_handler
*/

void				ft_exit(t_env *e, char *msg);
void				destroy(t_env *e);
void				reset(t_env *e);

#endif
