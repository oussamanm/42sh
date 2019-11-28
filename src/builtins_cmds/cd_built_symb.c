/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_symb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:12:01 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/25 19:51:55 by mfetoui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** - cd helper function;
*/

char		*dot_dot_path_2(char **arr, int cnt)
{
	char	*ret;
	int		i;

	ret = ft_strjoir("/", "", 0);
	i = -1;
	while (arr[++i] && i < cnt)
	{
		ret = ft_strjoir(ret, arr[i], 1);
		if (!(i + 1 == cnt) || !arr[i + 1])
			ret = ft_strjoir(ret, "/", 1);
	}
	return (ret);
}

/*
** - cd helper function;
*/

char		*dot_dot_path(char *s, char *pwd)
{
	int		cnt;
	char	**arr;
	char	*ret;
	int		i;

	i = -1;
	cnt = 0;
	ft_putendl_fd(pwd,1);
	while (s[++i])
		if (s[i] == '.' && s[i + 1] == '.')
			cnt++;
	arr = ft_strsplit(pwd, '/');
	i = 0;
	while (arr[i])
		i++;
	if (i <= cnt)
	{
		ft_free2d(arr);
		return (ft_strdup("/"));
	}
	cnt = (i > cnt) ? (i - cnt) : cnt;
	ret = dot_dot_path_2(arr, cnt);
	ft_free2d(arr);
	return (ret);
}

/*
** - correction path of cd cmd;
*/

char		*correct_path(char *path, t_cdpkg v)
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
	ret = ft_strjoir(getcwd(v.buff, 1024), path + i, 2);
	return (ret);
}

/*
** - this cmd work with symbolic path
*/

int			cd_symlink_1(char **pwd, char **oldpwd, int *var, t_cdpkg v)
{
	int		flag;
	char	*tmp;

	flag = 0;
	tmp = NULL;
	if (v.path[0] == '.' && v.path[1] == '.' && v.path[2] == '/' &&\
	(flag = 1))
		v.path = correct_path(v.path, v);
	else if (((ft_strcmp(v.path, ".") == 0 ||\
	ft_strcmp(v.path, "./") == 0) ||\
	(ft_strcmp(v.path, *pwd) == 0 && ft_strcmp(v.path, *oldpwd) == 0)) &&\
	*var && (flag = 2))
		v.path = ft_strdup(*pwd);
	else if (!(ft_strcmp(*pwd, v.path) == 0 ||\
	ft_strcmp(*oldpwd, v.path) == 0))
	{
		v.path = ft_strjoir(ft_strjoir(getcwd(v.buff, 1024), "/", 0)\
		, v.path, 1);
		ft_strdel(&tmp);
	}
	(flag == 1 || flag == 2) ? ft_strdel(&tmp) : 0;
	return (flag);
}

/*
** - this cmd work with symbolic path
*/

void		cd_symblink(char **pwd, char **oldpwd, int *var, t_cdpkg v)
{
	int		flag;

	ft_putendl_fd("before symb\n", 1);
	flag = cd_symlink_1(pwd, oldpwd, var, v);
	ft_putendl_fd("after symb\n", 1);
	if (flag == 1 || flag == 3)
		ft_set_vrb(ft_strjoir("OLDPWD=", ft_get_vrb("PWD", g_environ), 2),\
		&g_environ, 1);
	ft_set_vrb(ft_strjoir("PWD=", v.path, 0), &g_environ, 1);
	if (!flag)
		ft_set_vrb(ft_strjoir("OLDPWD=", getcwd(v.buff, 1024), 0),\
		&g_environ, 1);
	else if (flag == 2)
		ft_set_vrb(ft_strjoir("OLDPWD=", ft_get_vrb("PWD", g_environ), 2),\
		&g_environ, 1);
	// here
	chdir(v.path);
	ft_strdel(pwd);
	ft_strdel(oldpwd);
	*pwd = ft_strdup(getcwd(v.buff, 1024));
	// ft_putendl_fd(*pwd, 1);
	*oldpwd = ft_get_vrb("OLDPWD", g_environ);
	*var = 1;
}

