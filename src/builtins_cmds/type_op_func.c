/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_op_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:23:58 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/09 17:24:02 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - call this function when type cmd has no options;
*/

void	no_options(char *arg, int *flag)
{
	char *path;

	path = NULL;
	if ((path = lookup_hash(arg)))
	{
		path = ft_strdup(path);
		buil_putstr(arg, " is hashed ", path, 1);
	}
	else if (ft_check_built(arg))
		buil_putstr(arg, " is a shell builtin", NULL, 1);
	else if ((path = ft_find_path(arg, g_environ)))
		buil_putstr(arg, " is ", path, 1);
	else if ((*flag = 1))
		buil_putstr("42sh: type ", arg, ": not found", 2);
	ft_strdel(&path);
}

/*
** - serve -a option for cmd type
*/

int		a_option(char *arg)
{
	char	*path;
	int		ret;

	path = NULL;
	ret = 0;
	if (ft_check_built(arg) && (ret = 1))
		buil_putstr(arg, " is a shell builtin", NULL, 1);
	if ((path = ft_find_path(arg, g_environ)))
	{
		buil_putstr(arg, " is ", path, 1);
		ret = 1;
	}
	if (!ret)
		buil_putstr("42sh: type ", arg, ": not found", 2);
	return (ret);
}

/*
** - serve -p option for cmd type
*/

int		p_option(char *arg, int maj_p)
{
	char	*path;
	int		ret;

	path = NULL;
	ret = 0;
	if ((path = ft_find_path(arg, g_environ)) &&\
	!ft_check_built(arg) && (ret = 1))
		buil_putstr(path, NULL, NULL, 1);
	else if ((path = ft_find_path(arg, g_environ)) && \
	ft_check_built(arg) && maj_p && (ret = 1))
		buil_putstr(path, NULL, NULL, 1);
	ft_strdel(&path);
	if (!ret)
		buil_putstr("42sh: type ", arg, ": not found", 2);
	return (ret);
}

/*
** - serve -t option for cmd type
*/

int		t_option(char *arg, int flag)
{
	char	*path;
	int		ret;

	path = NULL;
	ret = 0;
	if (ft_check_built(arg) && flag && (ret = 1))
		buil_putstr("builtin", NULL, NULL, 1);
	else if ((path = ft_find_path(arg, g_environ)))
	{
		ret = 1;
		buil_putstr("file", NULL, NULL, 1);
	}
	if (!ret)
		buil_putstr("42sh: type ", arg, ": not found", 2);
	ft_strdel(&path);
	return (ret);
}

/*
** - serve -at option for cmd type
*/

int		at_option(char *arg)
{
	char	*path;
	int		ret;

	path = NULL;
	ret = 0;
	if (ft_check_built(arg) && (ret = 1))
		buil_putstr("builtin", NULL, NULL, 1);
	if ((path = ft_find_path(arg, g_environ)))
	{
		ret = 1;
		buil_putstr("file", NULL, NULL, 1);
	}
	if (!ret)
		buil_putstr("42sh: type ", arg, ": not found", 2);
	ft_strdel(&path);
	return (ret);
}
