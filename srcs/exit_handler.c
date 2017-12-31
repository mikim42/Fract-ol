/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 19:52:28 by mikim             #+#    #+#             */
/*   Updated: 2017/12/30 17:27:39 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	destroy(t_env *e)
{
	if (e->img)
		mlx_destroy_image(e->mlx, e->img);
	if (e->win)
		mlx_destroy_window(e->mlx, e->win);
}

void	ft_exit(t_env *e, char *msg)
{
	if (msg)
		ft_printf("fractol: illegal option -- %s\n", msg);
	destroy(e);
	exit(0);
}
