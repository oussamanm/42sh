/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:51:30 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/09 14:51:35 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_aliaspkg	*storeaddrstruct(t_aliaspkg *addr)
{
	static t_aliaspkg *ret;

	if (addr == NULL)
		return (ret);
	else
		ret = addr;
	return (ret);
}

void		pushtolist(char *string, int flag)
{
	t_alias		*node;
	t_aliaspkg	*data;
	int			i;

	data = storeaddrstruct(NULL);
	if (!(node = (t_alias *)malloc(sizeof(t_alias))))
		return ;
	i = -1;
	while (string[++i] && string[i] != '=')
		;
	node->shortcut = ft_strsub(string, 0, ++i);
	node->cmd = handleqoutes(ft_strdup(string + i));
	node->flag = flag;
	node->next = NULL;
	if (!data->head_ref && !data->tail_ref)
	{
		data->head_ref = node;
		data->tail_ref = data->head_ref;
	}
	else
	{
		data->tail_ref->next = node;
		data->tail_ref = node;
	}
}

void		createaliasfile(void)
{
	if (!(access("42shrc", F_OK) == 0))
		open("42shrc", O_CREAT, 0777);
}

void		importaliasfilecontent(void)
{
	char	*line;
	char	*tmp;
	int		i;
	int		fd;

	line = NULL;
	fd = open("42shrc", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		i = 0;
		while (line[i] && line[i] != '=')
			i++;
		tmp = ft_strsub(line, 0, i);
		removealiasbyelemorbyflag(tmp, 0);
		pushtolist(line, 1);
	}
}

char		*handleqoutes(char *str)
{
	char	*tmp;
	int		i;
	int		j;
	int		a;

	if (str[0] != '\'' && str[0] != '"')
		return (str);
	else
	{
		j = 0;
		while (str[j] && (str[j] == '\'' || str[j] == '"'))
			j++;
		a = str[j - 1];
		i = j - 1;
		while (str[++i] && str[i] != a)
			;
	}
	tmp = str;
	str = ft_strsub(str, j, i - j);
	ft_strdel(&tmp);
	return (str);
}
