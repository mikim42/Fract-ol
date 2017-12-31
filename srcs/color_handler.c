/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 00:22:53 by mikim             #+#    #+#             */
/*   Updated: 2017/12/31 02:46:05 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	color_gold_black(t_env *e)
{
	static int	palette[GOLD_BLACK] = {
		0xFA9600, 0xE18700, 0xC87800, 0xAF6900, 0x965A00,
		0x7D4B00, 0x643C00, 0x4B2D00, 0x321E00, 0x190F00,
		0x000000, 0x190F00, 0x321E00, 0x4B2D00, 0x643C00,
		0x7D4B00, 0x965A00, 0xAF6900, 0xC87800, 0xE18700
	};

	e->color_set = GOLD_BLACK;
	e->palette = palette;
}

void	color_warm(t_env *e)
{
	static int	palette[WARM] = {
		0xB48200, 0xB47800, 0xB46E00, 0xB46400, 0xB45A00,
		0xB45000, 0xB44600, 0xB43C00, 0xB43200, 0xB42800,
		0xB41E00, 0xAC1B0A, 0xA41814, 0x9C151E, 0x941228,
		0x8C0F32, 0x840C3C, 0x7C0946, 0x740650, 0x6C035A,
		0x640064, 0x6C035A, 0x740650, 0x7C0946, 0x840C3C,
		0x8C0F32, 0x941228, 0x9C151E, 0xA41814, 0xAC1B0A,
		0xB41E00, 0xB42800, 0xB43200, 0xB43C00, 0xB44600,
		0xB45000, 0xB45A00, 0xB46400, 0xB46E00, 0xB47800,
	};

	e->color_set = WARM;
	e->palette = palette;
}

void	color_cool(t_env *e)
{
	static int	palette[COOL] = {
		0x006464, 0x005A69, 0x00506E, 0x004673, 0x003C78,
		0x00327D, 0x002882, 0x001E87, 0x00148C, 0x000A91,
		0x000096, 0x0A009B, 0x1400A0, 0x1E00A5, 0x2800AA,
		0x3200AF, 0x3C00B4, 0x4600B9, 0x5000BE, 0x5A00C3,
		0x6400C8, 0x5A00B4, 0x5000A0, 0x46008C, 0x3C0078,
		0x320064, 0x280050, 0x1E003C, 0x140028, 0x0A0014,
		0x000000, 0x0A0014, 0x140028, 0x1E003C, 0x280050,
		0x320064, 0x3C0078, 0x46008C, 0x5000A0, 0x5A00B4,
		0x6400C8, 0x5A00C3, 0x5000BE, 0x4600B9, 0x3C00B4,
		0x3200AF, 0x2800AA, 0x1E00A5, 0x1400A0, 0x0A009B,
		0x000096, 0x000A91, 0x00148C, 0x001E87, 0x002882,
		0x00327D, 0x003C78, 0x004673, 0x00506E, 0x005A69,
	};

	e->color_set = COOL;
	e->palette = palette;
}

void	color_frequency(t_env *e)
{
	static int	palette[FREQUENCY];
	long double	frequency;
	int			i;

	frequency = 0;
	i = -1;
	if (!e->expose)
	{
		while (++i < FREQUENCY)
		{
			palette[i] += ((cos(frequency) + 1) * 127.5) * BLUE;
			palette[i] += ((sin(frequency) + 1) * 127.5) * GREEN;
			palette[i] += ((-cos(frequency) + 1) * 127.5) * RED;
			frequency += M_PI / FREQUENCY;
		}
	}
	e->color_set = FREQUENCY;
	e->palette = palette;
}

void	init_color(t_env *e)
{
	if (e->color < 0)
		e->color *= -1;
	if (e->color % 4 == 0)
		color_frequency(e);
	else if (e->color % 4 == 1)
		color_cool(e);
	else if (e->color % 4 == 2)
		color_warm(e);
	else
		color_gold_black(e);
}
