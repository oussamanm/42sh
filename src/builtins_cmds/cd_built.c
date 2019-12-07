/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:17:40 by mfilahi           #+#    #+#             */
/*   Updated: 2019/12/07 04:27:22 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Check Error cd builten
*/

int		ft_error_cd(char *path, char **arg, char *oldpath)
{
	int			bl_err;
	struct stat	st_stat;

	bl_err = 0;
	if (arg[0] != NULL && path != NULL && arg[0][0] == '~' &&
			ft_isalpha(arg[0][1]) && access(path, F_OK) == -1 && (bl_err = 1))
		print_error(oldpath, "cd :", FIL_NU, 0);
	else if (ft_strlen(path) >= 1024 && (bl_err = 1))
		print_error(oldpath, "cd :", "MAX PATH", 0);
	else if (access(path, F_OK) == -1 && (bl_err = 1))
		print_error(oldpath, "cd :", FIL_NS, 0);
	else
	{
		stat(path, &st_stat);
		if (!S_ISDIR(st_stat.st_mode) && (bl_err = 1))
			print_error(FIL_ND, "cd :", oldpath, 0);
		else if (access(path, X_OK) == -1 && (bl_err = 1))
			print_error(FIL_PD, "cd :", oldpath, 0);
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
					print_error(CD_OEMSG, "cd: -", &arg[i][j], 0);
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
** - get HOME or OLDPWD path;
*/

char	*get_path(char **arg, char **tmpenv, int flag)
{
	char	*path;

	path = NULL;
	if (*(arg + 0) && *(arg + 1))
		return (ft_putstr("42sh: cd: too many arguments\n") ? NULL : NULL);
	else if (*(arg) == NULL && !flag)
		return (ft_get_vrb("HOME", (tmpenv) ? tmpenv : g_environ));
	else if (*(arg) && *(arg)[0] == '-' && !*(arg + 1))
	{
		if (!(path = ft_get_vrb("OLDPWD", (tmpenv) ? tmpenv : g_environ)))
		{
			print_error("cd: OLDPWD not set", NULL, NULL, 0);
			return (NULL);
		}
		else
			return (path);
	}
	return (ft_strdup(*arg));
}

void	changedirectory(t_cdpkg *v)
{
	ft_set_vrb(ft_strjoir("OLDPWD=", ft_get_vrb("PWD", g_environ), 2)\
			, &g_environ, 1);
	chdir(v->path);
	ft_bzero(v->buff, 1024);
	ft_set_vrb(ft_strjoir("PWD=", (v->flag == P_flg) ?\
				getcwd(v->buff, 1024) : v->path, 0), &g_environ, 1);
}

/*
** the main func of cd called in shell.
*/

int		built_cd(char **arg, char **env)
{
	t_cdpkg		v;
	char		*oldpath;

	v.flag = 0;
	ft_bzero(v.buff, sizeof(v.buff));
	if ((v.index = cd_options(arg, 0, &v.flag)) == -1)
		return (EXIT_FAILURE);
	if (!(v.path = get_path(arg + v.index, env, v.flag)))
		return (EXIT_FAILURE);
	oldpath = ft_strdup(v.path);
	v.path = rmbackslashs(v.path);
	v.path = handlepath(&v);
	if (ft_error_cd(v.path, arg + 0, oldpath))
	{
		ft_strdel(&v.path);
		ft_strdel(&oldpath);
		return (EXIT_FAILURE);
	}
	changedirectory(&v);
	ft_strdel(&v.path);
	return (EXIT_SUCCESS);
}
