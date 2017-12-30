/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 22:33:33 by mikim             #+#    #+#             */
/*   Updated: 2017/12/29 22:50:59 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		expose_hooks(t_env *e)
{
	if (e->expose)
		fractol(e);
	else
		e->expose = 1;
	return (0);
}

int		motion_hooks(int x, int y, t_env *e)
{
	if (e->motion)
	{
		printf("x = [%d]\n", x);
		printf("y = [%d]\n", y);
		printf("e = [%p]\n", e);
	}
	return (0);
}

int		mouse_hooks(int button, int x, int y, t_env *e)
{
	long double	x_set;
	long double	y_set;

	x_set = (long double)(x - e->wid / 2) / (e->wid / 4);
	y_set = (long double)(y - e->hgt / 2) / (e->wid / 4);
	x_set /= e->zoom;
	y_set /= e->zoom;
	if (button == LEFT || button == RIGHT)
	{
		e->x_fix = button == LEFT ? e->x_fix + x_set : 0;
		e->y_fix = button == LEFT ? e->y_fix + y_set : 0;
	}
	else if (button == WHEEL_UP || button == WHEEL_DN)
	{
		e->x_fix = button == WHEEL_UP ?
		e->x_fix + x_set / 10 : e->x_fix - x_set / 10;
		e->y_fix = button == WHEEL_UP ?
		e->y_fix + y_set / 10 : e->y_fix - y_set / 10;
		e->zoom = button == WHEEL_UP ? e->zoom * 1.1 : e->zoom / 1.1;
		if (e->zoom_auto)
			e->max = button == WHEEL_UP ? e->max + 1 : e->max - 1;
	}
	fractol(e);
	return (0);
}

int		key_hooks(int code, t_env *e)
{
	CHANGE(code) ? change(e, code) : 0;
	MOVE(code) ? move(e, code) : 0;
	ZOOM(code) ? zoom(e, code) : 0;
	SIZE(code) ? size(e, code) : 0;
	ITER_UP(code) ? e->max += 1 : 0;
	ITER_DN(code) ? e->max -= 1 : 0;
	code == RESET ? reset(e) : 0;
	code == ESC ? ft_exit(e, NULL) : 0;
	if (code == MOTION_LOCK)
		e->motion = e->motion ? 0 : 1;
	if (code == ZOOM_AUTO)
		e->zoom_auto = e->zoom_auto ? 0 : 1;
	if (code == COLOR)
	{
		e->color++;
		init_color(e);
	}
	fractol(e);
	return (0);
}
