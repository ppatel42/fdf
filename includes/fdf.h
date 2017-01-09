/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:46:13 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/03 17:23:53 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>

# define ZOOM 0.1
# define ZOOMZ 10
# define ROTX 30 * 0.01745329252
# define ROTY 30 * 0.01745329252
# define ROTZ 45 * 0.01745329252
# define POS 0
# define PLACE 200
# define MOVE 20
# define WX 2560 / 2
# define WY 1440

typedef struct	s_map
{
	float			x;
	float			y;
	float			z;
	int				mz;
	int				color;
	struct s_map	*next;
}				t_map;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct	s_env
{
	void	*mlx;
	void	*win;
	void	*img;
	t_map	*cood;
	int		xlen;
	t_color	color;
}				t_env;

void			fdf(t_map *cood, int x, int y);
void			draw(t_env *a, t_map *cood, int f);
void			draw_line(t_env env, t_map *cood1, t_map *cood2);
void			ft_rotatex(t_map *cood, double theta);
void			ft_rotatey(t_map *cood, double theta);
void			ft_rotatez(t_map *cood, double theta);
int				key_hook(int key, t_env *a);
void			ft_zooma(t_map *cood, float zoom);

#endif
