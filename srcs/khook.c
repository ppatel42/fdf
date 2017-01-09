/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   khook.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:51:23 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/03 16:51:35 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>

void	ft_zooma(t_map *cood, float zoom)
{
	int		i;
	int		p;
	t_map	*new;

	i = 0;
	p = 0;
	while (i != 1 && p < 100)
	{
		new = cood;
		while (new)
		{
			new->x = (new->x - WX / 2) * zoom + WX / 2;
			new->y = (new->y - WY / 2) * zoom + WY / 2;
			new->z *= zoom;
			if ((new->x < WX / 8 && new->x > 0) \
					|| (new->y < WY / 8 && new->y > 0))
				i = 1;
			if (new->x < 0 || new->y < 0)
				i = 2;
			new = new->next;
		}
		if (i == 2)
			zoom = 0.9;
		p++;
	}
}

void	ft_move(t_env a, int key)
{
	t_map	*cood;

	cood = a.cood;
	while (cood)
	{
		if (key == 87)
			cood->y += MOVE;
		else if (key == 84)
			cood->y -= MOVE;
		else if (key == 83)
			cood->x += MOVE;
		else if (key == 85)
			cood->x -= MOVE;
		cood = cood->next;
	}
}

void	ft_zoom(t_env a, int key)
{
	t_map	*cood;
	float	zoom;

	cood = a.cood;
	if (key == 78)
		zoom = 1 - ZOOM;
	else
		zoom = 1 + ZOOM;
	while (cood)
	{
		cood->x = (cood->x - WX / 2) * zoom + WX / 2;
		cood->y = (cood->y - WY / 2) * zoom + WY / 2;
		cood->z *= zoom;
		cood = cood->next;
	}
}

void	ft_rotate(t_env a, int key)
{
	if (key == 126)
		ft_rotatex(a.cood, ROTX);
	else if (key == 125)
		ft_rotatex(a.cood, -ROTX);
	else if (key == 124)
		ft_rotatey(a.cood, ROTY);
	else if (key == 123)
		ft_rotatey(a.cood, -ROTY);
	else if (key == 2)
		ft_rotatez(a.cood, ROTZ);
	else if (key == 0)
		ft_rotatez(a.cood, -ROTZ);
}

int		key_hook(int key, t_env *a)
{
	mlx_clear_window(a->mlx, a->win);
	if (key == 53)
		exit(0);
	if (key == 84 || key == 87 || key == 85 || key == 83)
		ft_move(*a, key);
	if (key == 78 || key == 69)
		ft_zoom(*a, key);
	if ((key >= 123 && key <= 126) || key == 0 || key == 2)
		ft_rotate(*a, key);
	draw(a, a->cood, 0);
	if (key == 11)
		draw(a, a->cood, 1);
	return (0);
}
