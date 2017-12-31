/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 18:46:43 by mikim             #+#    #+#             */
/*   Updated: 2017/12/29 18:23:14 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

int		main(int ac, char **av)
{
	t_env	e;

	ft_bzero(&e, sizeof(e));
	if (ac > 1)
		ft_exit(&e, av[1]);
	parse(&e);
	fractol(&e);
	return (0);
}