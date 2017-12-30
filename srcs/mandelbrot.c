/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:51:32 by mikim             #+#    #+#             */
/*   Updated: 2017/12/29 23:28:24 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		mandelbrot_iter(t_env *e, long double x, long double y)
{
	long double	x_scale;
	long double	y_scale;
	long double	tmp;
	int			i;

	x_scale = (2.0 * x - e->wid) / (e->zoom * e->wid / 2) + e->x_fix;
	y_scale = (2.0 * y - e->hgt) / (e->zoom * e->hgt / 2) + e->y_fix;
	x = 0;
	y = 0;
	i = -1;
	while (x * x + y * y <= 4 && ++i < e->max)
	{
		tmp = x * x - y * y + x_scale;
		y = 2 * (x * y) + y_scale;
		x = tmp;
	}
	return (i);
}

void	mandelbrot(t_env *e, int thread, int n)
{
	int	x;
	int	y;
	int	iter;
	int	dist;

	y = -1;
	dist = n < THREAD - 1 ? thread + e->div : e->hgt;
	while (thread + ++y < dist)
	{
		x = -1;
		while (++x < e->wid)
		{
			iter = mandelbrot_iter(e, x, thread + y);
			e->data[(thread + y) * e->size / 4 + x] = iter == e->max ?
			0 : e->palette[iter % e->color_set];
		}
	}
}
