/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:38:48 by mikim             #+#    #+#             */
/*   Updated: 2017/12/29 20:23:48 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	init_mlx(t_env *e)
{
	e->win = mlx_new_window(e->mlx, e->wid, e->hgt, "Frcatol .mikim");
	e->img = mlx_new_image(e->mlx, e->wid, e->hgt);
	e->data = (int*)mlx_get_data_addr(e->img, &e->bits, &e->size, &e->endian);
}

void	init(t_env *e)
{
	e->wid = 300;
	e->hgt = 300;
	e->max = 10;
	e->zoom = 1;
	e->frac = mandel;
	e->mlx = mlx_init();
}

void	parse(t_env *e)
{
	init(e);
	init_mlx(e);
	init_color(e);
}
