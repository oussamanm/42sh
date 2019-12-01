/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 10:50:39 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/23 15:08:53 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	copy_line(char **ptr, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*ptr)[i] && (*ptr)[i] != '\n')
		i++;
	*line = ft_strsub(*ptr, 0, i);
	tmp = (*ptr);
	*ptr = ft_strdup(*ptr + i + 1);
	ft_strdel(&tmp);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*ptr;
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	int			ret;

	if (fd < 0)
		return (0);
	ft_bzero(buff, BUFFER_SIZE + 1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (!ptr)
			ptr = ft_strnew(1);
		tmp = ptr;
		ptr = ft_strjoin(ptr, buff);
		ft_strdel(&tmp);
		if (ft_strchr(ptr, '\n'))
			break ;
	}
	if (ret == 0)
		return (0);
	return ((ptr[0] != '\0') ? copy_line(&ptr, line) : 0);
}
