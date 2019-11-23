/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:17:40 by mfilahi           #+#    #+#             */
/*   Updated: 2019/11/16 11:58:00 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Check Error cd builten
*/

int		ft_error_cd(char *path, char **arg)
{
	int			bl_err;
	struct stat	st_stat;

	bl_err = 0;
	if (arg[0] != NULL && path != NULL && arg[0][0] == '~' &&
			ft_isalpha(arg[0][1]) && access(path, F_OK) == -1 && (bl_err = 1))
		print_error(path, "cd :", FIL_NU, 0);
	else if (ft_strlen(path) >= 1024 && (bl_err = 1))
		print_error(path, "cd :", "MAX PATH", 0);
	else if (access(path, F_OK) == -1 && (bl_err = 1))
		print_error(path, "cd :", FIL_NS, 0);
	else
	{
		stat(path, &st_stat);
		if (!S_ISDIR(st_stat.st_mode) && (bl_err = 1))
			print_error(FIL_ND, "cd :", path, 0);
		else if (access(path, X_OK) == -1 && (bl_err = 1))
			print_error(FIL_PD, "cd :", path, 0);
	}
	return (bl_err);
}

/*
** - check option of cd
*/

int		cd_options(char **arg, int j, int *flag)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i][0] == '-' && arg[i][1])
		{
			j = 0;
			while (arg[i][++j])
			{
				if (arg[i][j] == 'L')
					*flag = 0 | L_flg;
				else if (arg[i][j] == 'P')
					*flag = 0 | P_flg;
				else
				{
					print_error(CD_OEMSG, "42sh: cd: -", &arg[i][j], 0);
					return (-1);
				}
			}
		}
		else
			break ;
	}
	return (i);
}

/*
** - get home or OLDPWD path;
*/

char	*get_path(char **arg, char **tmpenv, int flag)
{
	if (*(arg + 0) && *(arg + 1))
		return (ft_putstr("42sh: cd: too many arguments\n") ? NULL : NULL);
	else if (*(arg) == NULL && !flag)
		return (ft_get_vrb("HOME", (tmpenv) ? tmpenv : g_environ));
	else if (*(arg) && *(arg)[0] == '-' && !*(arg + 1))
		return (ft_get_vrb("OLDPWD", (tmpenv) ? tmpenv : g_environ));
	return (ft_strdup(*arg));
}

/*
**	this func work with normal path
*/

void	cd_ordlink(char **pwd, char **oldpwd, int *var)
{
	t_cdpkg *v;

	v = store_addr_ofcdpkg(NULL);
	if (*var)
		ft_set_vrb(ft_strjoir("OLDPWD=", *pwd, 0), &g_environ, 1);
	else if (!*var)
		ft_set_vrb(ft_strjoir("OLDPWD=", getcwd(v->buff, 1024), 0)\
		, &g_environ, 1);
	if (ft_strncmp(v->path, "..", 2) == 0 && *var)
		v->path = dot_dot_path(v->path, *pwd);
	chdir(v->path);
	if (*var && !(ft_strcmp(*oldpwd, *pwd) == 0))
		ft_set_vrb(ft_strjoir("PWD=", v->path, 0), &g_environ, 1);
	else
		ft_set_vrb(ft_strjoir("PWD=", getcwd(v->buff, 1024), 0)\
		, &g_environ, 1);
	*var = 0;
}

/*
** the main func of cd called in shell.
*/

int		built_cd(char **arg, char **env)
{
	t_cdpkg		v;
	static char	*pwd;
	static char	*oldpwd;
	static int	var;

	v.flag = 0;
	ft_bzero(v.buff, sizeof(v.buff));
	store_addr_ofcdpkg(&v);
	if ((v.index = cd_options(arg, 0, &v.flag)) == -1)
		return (0);
	if (!(v.path = get_path(arg + v.index, env, v.flag)))
		return (0);
	if (ft_error_cd(v.path, arg + 0))
		return (0);
	lstat(v.path, &v.buf);
	if ((S_ISLNK(v.buf.st_mode) && !(v.flag == P_flg)) ||\
	(!(v.flag == P_flg) && var &&\
	(ft_strcmp(v.path, ".") == 0 ||\
	ft_strcmp(v.path, "./") == 0)))
		cd_symblink(&pwd, &oldpwd, &var);
	else
		cd_ordlink(&pwd, &oldpwd, &var);
	ft_bzero(v.buff, sizeof(v.buff));
	return (1);
}
