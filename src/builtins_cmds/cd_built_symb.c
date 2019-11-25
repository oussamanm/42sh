/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_symb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:12:01 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/16 12:48:05 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - store addr of cd cmd for easy free;
*/

t_cdpkg		*store_addr_ofcdpkg(t_cdpkg *v)
{
	static t_cdpkg *tmp;

	if (v)
		return ((tmp = v));
	return (tmp);
}

/*
** - cd helper functions
*/

char		*dot_dot_path(char *s, char *pwd)
{
	int		cnt;
	char	**arr;
	int		i;
	int		k;

	k = -1;
	cnt = 0;
	while (s[++k])
		if (s[k] == '.' && s[k + 1] == '.')
			cnt++;
	arr = ft_strsplit(pwd, '/');
	i = 0;
	while (arr[i])
		i++;
	if (i <= cnt)
		return (ft_strdup("/"));
	cnt = (i > cnt) ? (i - cnt) : cnt;
	arr[0] = ft_strjoir("/", arr[0], 0);
	i = 0;
	while (arr[++i] && i < cnt)
	{
		arr[i] = ft_strjoir("/", arr[i], 0);
		arr[0] = ft_strjoir(arr[0], arr[i], 0);
	}
	return (arr[0]);
}

/*
** - correction path of cd cmd;
*/

char		*correct_path(char *path, t_cdpkg *v)
{
	char	*ret;
	int		i;

	i = 0;
	while (path[i] &&\
			path[i] == '.' &&\
			path[i + 1] == '.' &&\
			path[i + 2] == '/')
	{
		chdir("..");
		if (path[i + 3] == '.')
			i += 3;
		else
			break ;
	}
	while (path[i] && path[i] == '.')
		i++;
	ret = ft_strjoin(getcwd(v->buff, 1024), path + i);
	return (ret);
}

/*
** - this cmd work with symbolic path
*/

int			cd_symlink_1(char **pwd, char **oldpwd, int *var)
{
	int		flag;
	t_cdpkg *v;

	v = store_addr_ofcdpkg(NULL);
	flag = 0;
	if (v->path[0] == '/' && (flag = 3))
	{
		chdir("/");
		readlink(v->path, v->buff, 1024);
		v->tmppath = ft_strdup(v->buff);
	}
	else if (v->path[0] == '.' && v->path[1] == '.' && v->path[2] == '/' &&\
	(flag = 1))
		v->path = correct_path(v->path, v);
	else if (((ft_strcmp(v->path, ".") == 0 ||\
	ft_strcmp(v->path, "./") == 0) ||\
	(ft_strcmp(v->path, *pwd) == 0 && ft_strcmp(v->path, *oldpwd) == 0)) &&\
	*var && (flag = 2))
		v->path = ft_strdup(*pwd);
	else if (!(ft_strcmp(*pwd, v->path) == 0 ||\
	ft_strcmp(*oldpwd, v->path) == 0))
		v->path = ft_strjoir(ft_strjoir(getcwd(v->buff, 1024), "/", 0)\
		, v->path, 1);
	return (flag);
}

/*
** - this cmd work with symbolic path
*/

void		cd_symblink(char **pwd, char **oldpwd, int *var)
{
	t_cdpkg	*v;
	int		flag;

	v = store_addr_ofcdpkg(NULL);
	flag = cd_symlink_1(pwd, oldpwd, var);
	if (flag == 1 || flag == 3)
		ft_set_vrb(ft_strjoir("OLDPWD=", ft_get_vrb("PWD", g_environ), 0),\
		&g_environ, 0);
	ft_set_vrb(ft_strjoir("PWD=", v->path, 0), &g_environ, 1);
	if (!flag)
		ft_set_vrb(ft_strjoir("OLDPWD=", getcwd(v->buff, 1024), 0),\
		&g_environ, 1);
	else if (flag == 2)
		ft_set_vrb(ft_strjoir("OLDPWD=", ft_get_vrb("PWD", g_environ), 0),\
		&g_environ, 0);
	ft_strdel(pwd);
	ft_strdel(oldpwd);
	*pwd = ft_get_vrb("PWD", g_environ);
	*oldpwd = ft_get_vrb("OLDPWD", g_environ);
	//ft_putendl(v->path);
	//ft_putendl(v->tmppath);
	chdir((flag == 3) ? v->tmppath : v->path);
	*var = 1;
}
