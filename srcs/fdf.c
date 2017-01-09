/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:47:17 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/03 17:30:52 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>

static void		ft_lstiter1(t_map *cood, int x, int y)
{
	while (cood)
	{
		cood->x = cood->x - x / 2;
		cood->y = cood->y - y / 2;
		cood = cood->next;
	}
}

void			ft_rotatex(t_map *cood, double theta)
{
	double		y;
	double		z;

	while (cood)
	{
		y = cood->y - WY / 2;
		z = cood->z;
		cood->y = y * cos(theta) - z * sin(theta) + WY / 2;
		cood->z = y * sin(theta) + z * cos(theta);
		cood = cood->next;
	}
}

void			ft_rotatey(t_map *cood, double theta)
{
	double		x;
	double		z;

	while (cood)
	{
		x = cood->x - WX / 2;
		z = cood->z;
		cood->x = x * cos(theta) + z * sin(theta) + WX / 2;
		cood->z = -x * sin(theta) + z * cos(theta);
		cood = cood->next;
	}
}

void			ft_rotatez(t_map *cood, double theta)
{
	double		x;
	double		y;

	while (cood)
	{
		x = cood->x - WX / 2;
		y = cood->y - WY / 2;
		cood->x = x * cos(theta) - y * sin(theta) + WX / 2;
		cood->y = x * sin(theta) + y * cos(theta) + WY / 2;
		cood = cood->next;
	}
}

void			fdf(t_map *cood, int x, int y)
{
	t_env	a;

	a.cood = cood;
	a.mlx = mlx_init();
	a.win = mlx_new_window(a.mlx, WX, WY, "FDF");
	a.xlen = x;
	ft_lstiter1(a.cood, x, y);
	ft_lstiter1(a.cood, -WX, -WY);
	ft_rotatex(a.cood, ROTX);
	ft_rotatey(a.cood, ROTY);
	ft_rotatez(a.cood, 0 * ROTZ);
	ft_zooma(a.cood, 1 + ZOOM);
	draw(&a, a.cood, 0);
	mlx_key_hook(a.win, key_hook, &a);
	mlx_loop(a.mlx);
}
