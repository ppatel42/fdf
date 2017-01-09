/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 15:49:30 by ppatel            #+#    #+#             */
/*   Updated: 2016/12/19 18:27:22 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_list_push_back(t_gnl **start, int fd)
{
	t_gnl	*cur;
	t_gnl	*new;

	cur = 0;
	if (!(new = (t_gnl *)malloc(sizeof(t_gnl))))
		return ;
	new->fd = fd;
	new->str = NULL;
	new->next = NULL;
	if (start)
	{
		cur = *start;
		while (cur && cur->next)
			cur = cur->next;
		if (cur)
			cur->next = new;
		else
			cur = new;
	}
}

t_gnl	*multi_fd(t_gnl **data, int fd)
{
	t_gnl	*cur;

	cur = *data;
	while (cur)
	{
		if ((cur)->fd == fd)
			return (cur);
		cur = (cur)->next;
		if (!cur)
		{
			ft_list_push_back(data, fd);
			cur = *data;
		}
	}
	if (!(*data = (t_gnl *)malloc(sizeof(t_gnl))))
		return (NULL);
	(*data)->fd = fd;
	(*data)->str = NULL;
	(*data)->next = NULL;
	return (*data);
}

int		check_read(char *buf, char **str, char **line)
{
	char	*tmp;

	if (buf == NULL && *str != NULL)
		if ((tmp = ft_strchr(*str, END)))
		{
			*tmp = '\0';
			*line = ft_strdup(*str);
			*str = ft_strdup(tmp + 1);
			tmp = NULL;
			return (1);
		}
	if (buf != NULL)
		if ((tmp = ft_strchr(buf, END)))
		{
			*tmp = '\0';
			*line = ft_strjoin(*str, buf);
			free(*str);
			*str = ft_strdup(tmp + 1);
			free(buf);
			tmp = NULL;
			return (1);
		}
	return (0);
}

char	*ft_strjoingnl(char *str, char *buf, t_gnl *tmpd)
{
	char	*tmp;

	if (tmpd)
	{
		tmp = ft_strdup(tmpd->str);
		free(tmpd->str);
		tmpd->str = NULL;
		return (tmp);
	}
	tmp = ft_strjoin(str, buf);
	free(str);
	return (tmp);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*data = NULL;
	t_gnl			*tmpd;
	char			*buf;
	int				ret;

	tmpd = multi_fd(&data, fd);
	if (tmpd->str)
		if (check_read(NULL, &tmpd->str, line))
			return (1);
	if (!(buf = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (check_read(buf, &tmpd->str, line))
			return (1);
		tmpd->str = ft_strjoingnl(tmpd->str, buf, NULL);
	}
	free(buf);
	if (ret == -1)
		return (-1);
	if (tmpd->str == NULL || *tmpd->str == 0)
		return (0);
	*line = ft_strjoingnl(NULL, NULL, tmpd);
	return (1);
}
