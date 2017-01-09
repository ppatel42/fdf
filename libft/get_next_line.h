/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppatel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:16:57 by ppatel            #+#    #+#             */
/*   Updated: 2016/12/19 18:29:32 by ppatel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# define BUFF_SIZE 100
# define END '\n'

typedef struct	s_gnl
{
	int				fd;
	char			*str;
	struct s_gnl	*next;
}				t_gnl;
int				get_next_line(const int fd, char **line);

#endif
