/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foolia.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:51:32 by mikim             #+#    #+#             */
/*   Updated: 2017/12/31 01:17:17 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		foolia_iter(t_env *e, long double r, long double i)
{
	double	r_sqr;
	double	i_sqr;
	int		iter;

	r = (2.0 * r - e->wid) / (e->zoom * e->wid / 2) + e->x_fix;
	i = (2.0 * i - e->hgt) / (e->zoom * e->hgt / 2) + e->y_fix;
	r_sqr = FT_SQR(r);
	i_sqr = FT_SQR(i);
	iter = -1;
	while (++iter < e->iter && r_sqr * r_sqr + i_sqr * i_sqr <= 4.0)
	{
		r_sqr = FT_SQR(r) - FT_SQR(i) + (e->motion_x * 4.0 / e->wid - 2.0);
		i_sqr = 2 * (r * i) + (e->motion_y * 4.0 / e->hgt - 2.0);
		r = r_sqr;
		i = -i_sqr;
	}
	iter++;
	return (iter);
}

void	foolia(t_env *e, int thread, int n)
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
			iter = foolia_iter(e, x, thread + y);
			e->data[(thread + y) * e->size / 4 + x] = iter == e->iter ?
			BLACK : e->palette[iter % e->color_set];
		}
	}
}
