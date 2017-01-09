/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:44:06 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/03 16:44:21 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>

static void		mlx_pxl_put(t_env a, int x, int y)
{
	char	*s;
	int		bpp;
	int		endian;
	int		sizeline;

	if (x < 0 || x >= WX || y < 0 || y >= WY)
		return ;
	s = mlx_get_data_addr(a.img, &bpp, &sizeline, &endian);
	if (endian == 0)
	{
		s[y * sizeline + x * bpp / 8 + 2] = a.color.r;
		s[y * sizeline + x * bpp / 8 + 1] = a.color.g;
		s[y * sizeline + x * bpp / 8] = a.color.b;
	}
	else
	{
		s[y * sizeline + x * bpp / 8 + 1] = a.color.r;
		s[y * sizeline + x * bpp / 8 + 2] = a.color.g;
		s[y * sizeline + x * bpp / 8 + 3] = a.color.b;
	}
}

static void		ft_linex(t_env env, int p1[], int p2[])
{
	float	m;
	float	k;

	m = (float)(p1[1] - p2[1]) / (float)(p1[0] - p2[0]);
	k = p2[1] - (m * p2[0]);
	if (p1[0] - p2[0] >= 0)
		while (p1[0] - p2[0] >= 0)
		{
			p1[1] = isnan(m * p1[0] + k) == 1 ? p1[1] : (m * p1[0] + k);
			mlx_pxl_put(env, p1[0], p1[1]);
			p1[0]--;
		}
	else if (p1[0] - p2[0] < 0)
		while (p2[0] - p1[0] >= 0)
		{
			p2[1] = isnan(m * p2[0] + k) == 1 ? p2[1] : (m * p2[0] + k);
			mlx_pxl_put(env, p2[0], p2[1]);
			p2[0]--;
		}
}

static void		ft_liney(t_env env, int p1[], int p2[])
{
	float	m;
	float	k;

	m = (float)(p1[1] - p2[1]) / (float)(p1[0] - p2[0]);
	k = p2[1] - (m * p2[0]);
	if (p1[1] - p2[1] > 0)
		while (p1[1] - p2[1] >= 0)
		{
			p1[0] = isnan((p1[1] - k) / m) == 1 ? p1[0] : ((p1[1] - k) / m);
			mlx_pxl_put(env, p1[0], p1[1]);
			p1[1]--;
		}
	else if (p1[1] - p2[1] < 0)
		while (p2[1] - p1[1] >= 0)
		{
			p2[0] = isnan((p2[1] - k) / m) == 1 ? p2[0] : ((p2[1] - k) / m);
			mlx_pxl_put(env, p2[0], p2[1]);
			p2[1]--;
		}
}

void			draw_line(t_env env, t_map *cood1, t_map *cood2)
{
	int		p1[2];
	int		p2[2];

	p1[0] = round(cood1->x);
	p1[1] = round(cood1->y);
	p2[0] = round(cood2->x);
	p2[1] = round(cood2->y);
	if (abs(p1[0] - p2[0]) >= abs(p1[1] - p2[1]))
		ft_linex(env, p1, p2);
	else
		ft_liney(env, p1, p2);
}
