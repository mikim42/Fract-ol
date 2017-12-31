/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:51:32 by mikim             #+#    #+#             */
/*   Updated: 2017/12/31 01:11:12 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		julia_iter(t_env *e, long double r, long double i)
{
	long double	r1;
	long double	i1;
	int			iter;

	r1 = (2.0 * r - e->wid) / (e->zoom * e->wid / 2) + e->x_fix;
	i1 = (2.0 * i - e->hgt) / (e->zoom * e->hgt / 2) + e->y_fix;
	iter = -1;
	while (++iter < e->iter && FT_SQR(r1) + FT_SQR(i1) <= 4.0)
	{
		r = r1;
		i = i1;
		r1 = FT_SQR(r) - FT_SQR(i) + (e->motion_x * 4.0 / e->wid - 2.0);
		i1 = 2 * (r * i) + (e->motion_y * 4.0 / e->hgt - 2.0);
	}
	return (iter);
}

void	julia(t_env *e, int thread, int n)
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
			iter = julia_iter(e, x, thread + y);
			e->data[(thread + y) * e->size / 4 + x] = iter == e->iter ?
			BLACK : e->palette[iter % e->color_set];
		}
	}
}
