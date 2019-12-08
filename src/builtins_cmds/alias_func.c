/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:51:30 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/02 12:32:38 by aboukhri         ###   ########.fr       */
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

void		pushtolist(char *key, char *value, int flag)
{
	t_alias		*node;
	t_aliaspkg	*data;

	data = storeaddrstruct(NULL);
	if (!(node = (t_alias *)malloc(sizeof(t_alias))))
		return ;
	node->shortcut = ft_strdup(key);
	node->equal = ft_strdup("=");
	node->cmd = handleqoutes(ft_strdup(value));
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
		ft_putstr_fd("=", 1);
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
		if ((fd = open(".42shrc", O_CREAT, 00644)) == -1)
			return ;
		close(fd);
	}
}

/*
** - import alias content file to list;
*/

void		importaliasfilecontent(char *tmp)
{
	char	*line;
	int		count;
	int		fd;

	line = NULL;
	count = 0;
	(void)tmp;
	if ((fd = open(".42shrc", O_RDONLY)) == -1)
		return ;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strcmp(line, "") == 0)
		{
			ft_strdel(&line);
			continue ;
		}
		else
		{
			if ((ft_strncmp(line, "alias", 5)) == 0)
				importaliasfilecontent_1(line + 5);
			ft_strdel(&line);
		}
	}
	close(fd);
}
