/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 17:48:52 by mikim             #+#    #+#             */
/*   Updated: 2017/12/31 03:02:34 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	reset(t_env *e)
{
	destroy(e);
	e->wid = 300;
	e->hgt = 300;
	e->zoom = 1.0;
	e->y_fix = 0;
	e->x_fix = 0;
	e->iter = DEFAULT;
	if (e->frac == jul || e->frac == fool)
		e->motion = 1;
	init_mlx(e);
	init_color(e);
}

void	size(t_env *e, int code)
{
	if (code == WID_DN)
		e->wid -= WID_RATE;
	else if (code == WID_UP)
		e->wid += WID_RATE;
	else if (code == HGT_DN)
		e->hgt -= HGT_RATE;
	else if (code == HGT_UP)
		e->hgt += HGT_RATE;
	if (e->wid > WID_MAX)
		e->wid = WID_MAX;
	else if (e->wid < WID_MIN)
		e->wid = WID_MIN;
	if (e->hgt > HGT_MAX)
		e->hgt = HGT_MAX;
	else if (e->hgt < HGT_MIN)
		e->hgt = HGT_MIN;
	destroy(e);
	init_mlx(e);
	init_color(e);
}

void	zoom(t_env *e, int code)
{
	if (code == ZOOM_IN)
	{
		e->zoom *= ZOOM_RATE;
		e->zoom_auto ? e->iter++ : 0;
	}
	else if (code == ZOOM_OUT)
	{
		e->zoom /= ZOOM_RATE;
		e->zoom_auto ? e->iter-- : 0;
	}
}

void	move(t_env *e, int code)
{
	if (code == MOVE_LEFT)
		e->x_fix -= MOVE_RATE / e->zoom;
	else if (code == MOVE_UP)
		e->y_fix += MOVE_RATE / e->zoom;
	else if (code == MOVE_RIGHT)
		e->x_fix += MOVE_RATE / e->zoom;
	else if (code == MOVE_DOWN)
		e->y_fix -= MOVE_RATE / e->zoom;
}

void	change(t_env *e, int code)
{
	e->motion = 0;
	if (MANDELBROT(code))
		e->frac = mandel;
	else if (JULIA(code))
	{
		e->motion = 1;
		e->frac = jul;
	}
	else if (FOOLIA(code))
	{
		e->motion = 1;
		e->frac = fool;
	}
	else if (SHIP(code))
		e->frac = ship;
	else if (TRICORN(code))
		e->frac = corn;
	reset(e);
}
