/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 15:51:32 by mikim             #+#    #+#             */
/*   Updated: 2018/01/04 17:13:54 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		mandelbrot_iter(t_env *e, long double r, long double i)
{
	long double	r_scale;
	long double	i_scale;
	long double r1;
	long double i1;
	int			iter;

	r_scale = (2.0 * r - e->wid) / (e->zoom * e->wid / 2) + e->x_fix;
	i_scale = (2.0 * i - e->hgt) / (e->zoom * e->hgt / 2) + e->y_fix;
	r = 0;
	i = 0;
	r1 = 0;
	i1 = 0;
	iter = -1;
	while (++iter < e->iter && r1 + i1 <= 4)
	{
		i = FT_SQR(r + i) - r1 - i1 + i_scale;
		r = r1 - i1 + r_scale;
		i1 = FT_SQR(i);
		r1 = FT_SQR(r);
	}
	return (iter);
}
/*
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
			e->data[(thread + y) * e->size / 4 + x] = iter == e->iter ?
			BLACK : e->palette[iter % e->color_set];
		}
	}
}
*/
// multithreading

void	*mandelbrot_thread(void *arg)
{
	t_thread2 *t = (t_thread2*)arg;

//	pthread_mutex_lock(&t->e->mutex2);
	for (int x = t->x; x < t->x1; x++)
	{
		int iter = mandelbrot_iter(t->e, x, t->y);
		t->e->data[t->y * t->e->size / 4 + x] = iter == t->e->iter ?
		BLACK : t->e->palette[iter % t->e->color_set];
	}
//	pthread_mutex_unlock(&t->e->mutex2);
	pthread_exit(NULL);
}

void	mandelbrot(t_env *e, int thread, int n)
{
	pthread_t t[THREAD];
	t_thread2 t_arg[THREAD];
	int	x;
	int	y;
	int	dist;

	y = -1;
	dist = n < THREAD - 1 ? thread + e->div : e->hgt;
	while (thread + ++y < dist)
	{
		x = -1;
		while (++x < THREAD)
		{
			t_arg[x].e = e;
			t_arg[x].x = x * (e->wid / THREAD);
			t_arg[x].x1 = x == THREAD - 1 ? 
			e->wid : (x + 1) * (e->wid / THREAD);
			t_arg[x].y = thread + y;
			pthread_create(&t[x], NULL, mandelbrot_thread, &t_arg[x]);
		}
		x = -1;
		while (++x < THREAD)
			pthread_join(t[x], NULL);
	}
}
