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

char		*dot_dot_path(char *s, char *pwd, int i, int cnt)
{
	char	**arr;
	char	*ret;
	char	*ptr;

	ptr = pwd;
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
		ft_strdel(&ptr);
		return (ft_strdup("/"));
	}
	cnt = (i > cnt) ? (i - cnt) : cnt;
	ret = dot_dot_path_2(arr, cnt);
	ft_free2d(arr);
	ft_strdel(&ptr);
	return (ret);
}

/*
** - correction path of cd cmd;
*/

char		*cd_backwardpoints(char *pathcopy, t_cdpkg *v, int *i)
{
	char	*tmp;

	*i = 0;
	while (pathcopy[*(i)] &&\
			pathcopy[*(i)] == '.' &&\
			pathcopy[*(i) + 1] == '.' &&\
			pathcopy[*(i) + 2] == '/')
	{
		chdir("..");
		if (pathcopy[*i + 3] == '.')
			*i += 3;
		else
			break ;
	}
	while (pathcopy[*i] && pathcopy[*i] == '.')
		(*i)++;
	tmp = pathcopy;
	ft_bzero(v->buff, 1024);
	pathcopy = ft_strjoir(getcwd(v->buff, 1024), pathcopy + *(i), 0);
	ft_strdel(&tmp);
	return (pathcopy);
}

/*
** - this cmd work with cd_symblink
*/

char		*cd_relativepath(char *pathcopy, t_cdpkg *v)
{
	ft_bzero(v->buff, 1024);
	getcwd(v->buff, 1024);
	pathcopy = ft_strjoir(v->buff, ft_strjoir("/", pathcopy, 2), 2);
	return (pathcopy);
}

/*
** - this cmd work with symbolic path
*/

void		cd_symblink(t_cdpkg *v)
{
	char	*pathcopy;
	char	*tmp;
	int		i;

	tmp = NULL;
	pathcopy = ft_strdup(v->path);
	if (pathcopy[0] == '.' && pathcopy[1] == '.')
	{
		pathcopy = cd_backwardpoints(pathcopy, v, &i);
		tmp = v->path;
		v->path = ft_strdup(v->path + (i - 1));
		ft_strdel(&tmp);
	}
	else if (pathcopy[0] == '.' && pathcopy[1] != '.')
	{
		tmp = pathcopy;
		pathcopy = ft_get_vrb("PWD", g_environ);
		ft_strdel(&tmp);
	}
	else if (pathcopy[0] != '/')
		pathcopy = cd_relativepath(pathcopy, v);
	ft_set_vrb(ft_strjoir("OLDPWD=", ft_get_vrb("PWD", g_environ), 2),\
		&g_environ, 1);
	ft_set_vrb(ft_strjoir("PWD=", pathcopy, 2), &g_environ, 1);
	chdir(v->path);
}
