/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:38:48 by mikim             #+#    #+#             */
/*   Updated: 2018/01/02 11:13:54 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	usage(void)
{
	ft_printf("{SET:BO}%s\n", "1: MANDELBROT");
	ft_printf("%s\n", "2: JULIA");
	ft_printf("%s\n", "3: FOOLIA");
	ft_printf("%s\n", "4: BURNING SHIP");
	ft_printf("%s\n\n", "5: TRICORN");
	ft_printf("%s\n", "  LOCK: SPACE");
	ft_printf("%s\n", "  MOVE: WASD or LEFT CLICK");
	ft_printf("%s\n\n", "CENTER: RIGHT CLICK");
	ft_printf("%s\n", "ZOOM   IN: WHEEL UP or [");
	ft_printf("%s\n", "ZOOM  OUT: WHEEL DOWN or ]");
	ft_printf("%s\n\n", "ZOOM AUTO: Z");
	ft_printf("%s\n", "ITERATION: +-");
	ft_printf("%s\n", "    COLOR: C");
	ft_printf("%s\n", "     SIZE: ARROW");
	ft_printf("%s\n\n", "    RESET: R");
	ft_printf("%s{OFF}\n", "EXIT: ESC");
}

void	init_mlx(t_env *e)
{
	char		*tmp;
	static char	*s[5] = {
		"Mandelbrot",
		"Julia",
		"Foolia",
		"Burning Ship",
		"Tricorn"
	};

	tmp = ft_strjoin(s[e->frac - 1], " .mikim");
	e->win = mlx_new_window(e->mlx, e->wid, e->hgt, tmp);
	e->img = mlx_new_image(e->mlx, e->wid, e->hgt);
	e->data = (int*)mlx_get_data_addr(e->img, &e->bits, &e->size, &e->endian);
	free(tmp);
}

void	init(t_env *e)
{
	e->wid = 300;
	e->hgt = 300;
	e->iter = DEFAULT;
	e->zoom = 1;
	e->frac = mandel;
	e->mlx = mlx_init();
	pthread_mutex_init(&e->mutex, NULL);
}

void	parse(t_env *e)
{
	init(e);
	init_mlx(e);
	init_color(e);
	usage();
}
