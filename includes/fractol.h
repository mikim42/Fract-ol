/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 18:40:17 by mikim             #+#    #+#             */
/*   Updated: 2018/01/02 11:17:02 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>
# include <mlx.h>
# include <math.h>
# include <pthread.h>

# define THREAD 16
# define MAX 1000
# define DEFAULT 100

# define WID_MAX 1900
# define WID_MIN 100
# define HGT_MAX 1200
# define HGT_MIN 100

# define FREQUENCY 64
# define GOLD_BLACK 20
# define COOL 60 
# define WARM 40

# define RED 65536
# define GREEN 256
# define BLUE 1
# define WHITE 0xFFFFFF
# define BLACK 0x000000

# define WID_RATE 100
# define HGT_RATE 100
# define ZOOM_RATE 1.1
# define MOVE_RATE 0.05

# define KEY 2
# define MOUSE 4
# define MOTION 6
# define EXPOSE 12
# define CLOSE 17

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
# define FOOLIA(x) (x == 20 || x == 85)
# define SHIP(x) (x == 21 || x == 86)
# define TRICORN(x) (x == 23 || x == 87)

typedef	enum		e_fractol
{
	mandel = 1,
	jul,
	fool,
	ship,
	corn
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
	int				iter;
	int				div;
	int				*palette;
	int				color;
	int				color_set;
	long double		x_fix;
	long double		y_fix;
	long double		zoom;
	int				zoom_auto;
	int				motion;
	int				motion_x;
	int				motion_y;
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
int					mandelbrot_iter(t_env *e, long double r, long double i);

/*
**					julia
*/

void				julia(t_env *e, int thread, int n);
int					julia_iter(t_env *e, long double r, long double i);

/*
**					foolia
*/

void				foolia(t_env *e, int thread, int n);
int					foolia_iter(t_env *e, long double r, long double i);

/*
**					burning_ship
*/

void				burning_ship(t_env *e, int thread, int n);
int					ship_iter(t_env *e, long double r, long double i);

/*
**					tricorn
*/

void				tricorn(t_env *e, int thread, int n);
int					tricorn_iter(t_env *e, long double r, long double i);

/*
**					color_handler
*/

void				init_color(t_env *e);
void				color_frequency(t_env *e);
void				color_cool(t_env *e);
void				color_warm(t_env *e);
void				color_gold_black(t_env *e);

/*
**					hook_handler
*/

int					key_hooks(int code, t_env *e);
int					mouse_hooks(int button, int x, int y, t_env *e);
int					motion_hooks(int x, int y, t_env *e);
int					expose_hooks(t_env *e);
int					exit_hooks(t_env *e);

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
