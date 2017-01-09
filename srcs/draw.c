/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:45:47 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/03 16:45:53 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>

static t_map	*ft_list_at(t_map *begin_list, size_t nbr)
{
	size_t	i;

	i = 1;
	while (begin_list && i < nbr)
	{
		begin_list = begin_list->next;
		i++;
	}
	if (i == nbr)
		return (begin_list);
	return (0);
}

static void		color(t_env *e, int a, int b, int f)
{
	int		color;

	if (a > 0 && a == b && f == 0)
		color = 0x00FF00;
	else if (a > 0 && a == b && f == 1)
		color = 0xFFFFFF;
	else if (a < 0 && b < 0 && f == 0)
		color = 0x0000FF;
	else if (a > 0 || b > 0)
		color = 0x939393;
	else if (f == 1)
		color = 0;
	else
		color = 0xFF0000;
	e->color.b = color % 256;
	e->color.g = ((color - e->color.b) / (256)) % 256;
	e->color.r = (color - e->color.b - (e->color.g * 256)) / 65536;
}

void			draw(t_env *a, t_map *cood, int f)
{
	t_map	*new;
	int		i;

	i = 0;
	a->img = mlx_new_image(a->mlx, WX, WY);
	new = ft_list_at(cood, a->xlen + 1);
	while (cood && cood->next)
	{
		color(a, cood->mz, cood->next->mz, f);
		if (++i % a->xlen != 0)
			draw_line(*a, cood, cood->next);
		if (new)
		{
			color(a, cood->mz, new->mz, f);
			draw_line(*a, cood, new);
			new = new->next;
		}
		cood = cood->next;
	}
	mlx_put_image_to_window(a->mlx, a->win, a->img, 0, 0);
}
