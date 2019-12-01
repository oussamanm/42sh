/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 10:50:39 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/01 23:47:52 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		copy_in_line(char **text, char **line)
{
	char	*tmp;
	char	*p;
	int		i;

	p = *text;
	i = 0;
	while (p[i] && p[i] != '\n')
		i++;
	tmp = ft_strnew(i);
	i = 0;
	while (*p && *p != '\n')
		tmp[i++] = *p++;
	tmp[i] = '\0';
	*line = ft_strdup(tmp);
	free(tmp);
	tmp = *text;
	*text = ft_strdup(*text + i + 1);
	ft_strdel(&tmp);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*text[65536];
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	if (fd < 0 || read(fd, buff, 0) < 0)
		return (-1);
	while ((ret = read(fd, buff, BUFFER_SIZE)))
	{
		if (text[fd] == NULL)
			text[fd] = ft_strnew(1);
		buff[ret] = '\0';
		text[fd] = ft_strjoir(text[fd], buff, 1);
		if (ft_strchr(text[fd], '\n'))
			break ;
	}
	if (*text[fd] != '\0')
		return (copy_in_line(&text[fd], line));
	return (-1);
}
