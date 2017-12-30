/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 00:22:53 by mikim             #+#    #+#             */
/*   Updated: 2017/12/30 00:00:57 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	color_custom(t_env *e)
{
	if (e->palette)
		free(e->palette);
	e->color_set = 20;
	e->palette = ft_memalloc(sizeof(int) * e->color_set);
	e->palette[0] = 0 * RED + 0 * GREEN + 250 * BLUE;
	e->palette[1] = 25 * RED + 15 * GREEN + 225 * BLUE;
	e->palette[2] = 50 * RED + 30 * GREEN + 200 * BLUE;
	e->palette[3] = 75 * RED + 45 * GREEN + 175 * BLUE;
	e->palette[4] = 100 * RED + 60 * GREEN + 150 * BLUE;
	e->palette[5] = 125 * RED + 75 * GREEN + 125 * BLUE;
	e->palette[6] = 150 * RED + 90 * GREEN + 100 * BLUE;
	e->palette[7] = 175 * RED + 105 * GREEN + 75 * BLUE;
	e->palette[8] = 200 * RED + 120 * GREEN + 50 * BLUE;
	e->palette[9] = 225 * RED + 135 * GREEN + 25 * BLUE;
	e->palette[10] = 250 * RED + 150 * GREEN + 0 * BLUE;
	e->palette[11] = 225 * RED + 135 * GREEN + 25 * BLUE;
	e->palette[12] = 200 * RED + 120 * GREEN + 50 * BLUE;
	e->palette[13] = 175 * RED + 105 * GREEN + 75 * BLUE;
	e->palette[14] = 150 * RED + 90 * GREEN + 100 * BLUE;
	e->palette[15] = 125 * RED + 75 * GREEN + 125 * BLUE;
	e->palette[16] = 100 * RED + 60 * GREEN + 150 * BLUE;
	e->palette[17] = 75 * RED + 45 * GREEN + 175 * BLUE;
	e->palette[18] = 50 * RED + 30 * GREEN + 200 * BLUE;
	e->palette[19] = 25 * RED + 15 * GREEN + 225 * BLUE;
}

void	color_red(t_env *e)
{
	long double	frequency;
	int			i;

	if (e->palette)
		free(e->palette);
	e->palette = ft_memalloc(sizeof(int) * PALETTE);
	frequency = 0;
	i = -1;
	while (++i < PALETTE)
	{
		e->palette[i] += ((cos(frequency) + 1) * 127.5) * RED;
		e->palette[i] += ((sin(frequency) + 1) * 127.5) * GREEN;
		e->palette[i] += ((-cos(frequency) + 1) * 127.5) * BLUE;
		frequency += M_PI / PALETTE;
	}
	e->color_set = PALETTE;
}

void	color_green(t_env *e)
{
	long double	frequency;
	int			i;

	if (e->palette)
		free(e->palette);
	e->palette = ft_memalloc(sizeof(int) * PALETTE);
	frequency = 0;
	i = -1;
	while (++i < PALETTE)
	{
		e->palette[i] += ((cos(frequency) + 1) * 127.5) * GREEN;
		e->palette[i] += ((sin(frequency) + 1) * 127.5) * RED;
		e->palette[i] += ((-cos(frequency) + 1) * 127.5) * BLUE;
		frequency += M_PI / PALETTE;
	}
	e->color_set = PALETTE;
}

void	color_blue(t_env *e)
{
	long double	frequency;
	int			i;

	if (e->palette)
		free(e->palette);
	e->palette = ft_memalloc(sizeof(int) * PALETTE);
	frequency = 0;
	i = -1;
	while (++i < PALETTE)
	{
		e->palette[i] += ((cos(frequency) + 1) * 127.5) * BLUE;
		e->palette[i] += ((sin(frequency) + 1) * 127.5) * GREEN;
		e->palette[i] += ((-cos(frequency) + 1) * 127.5) * RED;
		frequency += M_PI / PALETTE;
	}
	e->color_set = PALETTE;
}

void	init_color(t_env *e)
{
	if (e->color < 0)
		e->color *= -1;
	if (e->color % 4 == 0)
		color_red(e);
	else if (e->color % 4 == 1)
		color_green(e);
	else if (e->color % 4 == 2)
		color_blue(e);
	else
		color_custom(e);
}
