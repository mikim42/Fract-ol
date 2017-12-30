/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 21:52:28 by mikim             #+#    #+#             */
/*   Updated: 2017/12/29 23:19:25 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	cross_hair(t_env *e)
{
	e->data[(e->hgt / 2 - 1) * e->size / 4 + (e->wid / 2)] = WHITE;
	e->data[(e->hgt / 2 - 2) * e->size / 4 + (e->wid / 2)] = WHITE;
	e->data[(e->hgt / 2 + 1) * e->size / 4 + (e->wid / 2)] = WHITE;
	e->data[(e->hgt / 2 + 2) * e->size / 4 + (e->wid / 2)] = WHITE;
	e->data[(e->hgt / 2) * e->size / 4 + (e->wid / 2) - 1] = WHITE;
	e->data[(e->hgt / 2) * e->size / 4 + (e->wid / 2) - 2] = WHITE;
	e->data[(e->hgt / 2) * e->size / 4 + (e->wid / 2) + 1] = WHITE;
	e->data[(e->hgt / 2) * e->size / 4 + (e->wid / 2) + 2] = WHITE;
}

void	*plot(void *arg)
{
	t_thread	*t;

	t = (t_thread*)arg;
	pthread_mutex_lock(&t->e->mutex);
	if (t->e->frac == mandel)
		mandelbrot(t->e, t->thread, t->n);
//	else if (t->e->frac == jul)
//		julia(t->e, t->thread, t->n);
//	else if (t->e->frac == pt)
//		tree(t->e, t->thread, t->n);
	pthread_mutex_unlock(&t->e->mutex);
	pthread_exit(NULL);
}

void	fractol(t_env *e)
{
	pthread_t	thread[THREAD];
	t_thread	t[THREAD];
	int			i;

	i = -1;
	e->div = e->hgt / THREAD;
	while (++i < THREAD)
	{
		t[i].e = e;
		t[i].n = i;
		t[i].thread = e->div * i;
		pthread_create(&thread[i], NULL, plot, &t[i]);
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(thread[i], NULL);
	cross_hair(e);
	printf("dope!\n");
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	mlx_hook(e->win, KEY, 0, key_hooks, e);
	mlx_hook(e->win, MOTION, 0, motion_hooks, e);
	mlx_hook(e->win, MOUSE, 0, mouse_hooks, e);
	mlx_hook(e->win, EXPOSE, 0, expose_hooks, e);
	mlx_loop(e->mlx);
}
