/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 01:11:52 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/02 11:26:30 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		copy_in_line(char **text, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (ft_strchr(*text, '\n'))
	{
		while ((*text)[i] && (*text)[i] != '\n')
			i++;
		*line = ft_strsub(*text, 0, i);
		tmp = *text;
		*text = ft_strdup(*text + i + 1);
		ft_strdel(&tmp);
	}
	else
	{
		while ((*text)[i] && (*text)[i] != '\n')
			i++;
		*line = ft_strsub(*text, 0, i);
		tmp = *text;
		*text = ft_strdup(*text + i);
		ft_strdel(&tmp);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*text[65536];
	char		buff[BUFFER_SIZE + 1];
	char		*tmp;
	int			ret;

	tmp = NULL;
	if (fd < 0)
		return (-1);
	if (text[fd] == NULL)
		text[fd] = ft_strnew(1);
	while ((ret = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = text[fd];
		text[fd] = ft_strjoin(text[fd], buff);
		ft_strdel(&tmp);
		if (ft_strchr(text[fd], '\n'))
			break ;
	}
	if (*text[fd] != '\0')
		return (copy_in_line(&text[fd], line));
	free(text[fd]);
	text[fd] = NULL;
	return (0);
}
