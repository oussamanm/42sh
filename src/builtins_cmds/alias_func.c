/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:51:30 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/01 22:44:47 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - store add of list that relate to alias for easy free;
*/

t_aliaspkg	*storeaddrstruct(t_aliaspkg *addr)
{
	static t_aliaspkg *ret;

	if (addr == NULL)
		return (ret);
	else
		ret = addr;
	return (ret);
}

/*
** - push alias into list;
*/

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

/*
** - print all aliases;
*/

void		printlist(void)
{
	t_aliaspkg	*data;
	t_alias		*curr;

	data = storeaddrstruct(NULL);
	curr = data->head_ref;
	while (curr)
	{
		ft_putstr_fd("alias ", 1);
		ft_putstr_fd(curr->shortcut, 1);
		(curr->cmd[0] != '\'') ? ft_putchar_fd('\'', 1) : 0;
		ft_putstr_fd(curr->cmd, 1);
		(curr->cmd[ft_strlen(curr->cmd) - 1] != '\'') ? ft_putendl_fd("\'", 1)\
		: ft_putchar_fd('\n', 1);
		curr = curr->next;
	}
}

/*
** - create file of aliases for permanent aliases
*/

void		createaliasfile(void)
{
	int fd;

	fd = 0;
	if (!(access(".42shrc", F_OK) == 0))
	{
		fd = open(".42shrc", O_CREAT, 00600);
		close(fd);
	}
}

/*
** - import alias content file to list;
*/

void		importaliasfilecontent(char *tmp)
{
	char	*line;
	int		i;
	int		count;
	int		fd;

	line = NULL;
	count = 0;
	fd = open(".42shrc", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "") == 0)
			continue ;
		else
		{
			i = 0;
			while (line[i] && line[i] != '=')
				i++;
			tmp = ft_strsub(line, 0, i);
			rm_alias_by_elem_flag(tmp, 0, 0);
			pushtolist(line, 1);
			ft_strdel(&tmp);
			ft_strdel(&line);
		}
	}
	close(fd);
}
