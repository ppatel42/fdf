/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 17:36:17 by ppatel            #+#    #+#             */
/*   Updated: 2017/01/03 22:31:57 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <mlx.h>

static t_map	*ft_create_elem(int x, int y, int z, int color)
{
	int		i;
	t_map	*new;

	i = 0;
	if (!(new = (t_map *)malloc(sizeof(t_map))))
		return (NULL);
	new->x = x;
	new->y = y;
	new->z = z;
	new->mz = z;
	new->color = color;
	new->next = NULL;
	return (new);
}

static void		ft_lst_add_back(t_map **start, t_map *new)
{
	t_map	*cur;
	t_map	*lst;

	lst = *start;
	if (lst)
	{
		cur = *start;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
	else
		lst = new;
	*start = lst;
}

static void		ft_readmap(int fd, char *line, t_map *map)
{
	char	**tab;
	int		x;
	int		y;
	t_map	*tmp;
	t_map	*new;

	tmp = NULL;
	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		tab = ft_strsplit(line, ' ');
		while (tab && tab[x])
		{
			new = ft_create_elem(x, y, ft_atoi(tab[x]), 0);
			ft_lst_add_back(&tmp, new);
			if (x == 0 && y == 0)
				map = tmp;
			tmp = new;
			x++;
		}
		y++;
	}
	fdf(map, x, y);
}

static int		ft_check(int fd, char *line)
{
	char	**tab;
	int		x;
	int		y;
	int		i;

	y = 0;
	while (get_next_line(fd, &line) > 0)
	{
		x = 0;
		tab = ft_strsplit(line, ' ');
		while (tab && tab[x])
		{
			if ((tab[x][0] < '0' || tab[x][0] > '9') && tab[x][0] != '-')
				return (-1);
			x++;
		}
		if (y == 0)
			i = x;
		if (x != i || x == 0)
			return (-1);
		y++;
	}
	if (y == 0 || (y == 1 && x == 1))
		return (-1);
	return (0);
}

int				main(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		ft_putendl("usage: ./fdf [use 1 valid file]");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (ft_check(fd, NULL) == -1)
	{
		ft_putendl("Invalid Map");
		return (0);
	}
	close(fd);
	fd = open(argv[1], O_RDONLY);
	ft_readmap(fd, NULL, NULL);
	close(fd);
}
