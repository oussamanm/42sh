/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 12:17:40 by mfilahi           #+#    #+#             */
/*   Updated: 2019/09/25 12:17:43 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Check Error cd builten : O
*/

int			ft_error_cd(char *path, char **arg)
{
	int			bl_err;
	struct stat	st_stat;

	bl_err = 0;
    ft_putendl_fd(path, 2);
	if (arg[0] != NULL && path != NULL && arg[0][0] == '~' &&
			ft_isalpha(arg[0][1]) && access(path, F_OK) == -1 && (bl_err = 1))
		ft_print_error(path, "cd :", FIL_NU, 0);
	else if (ft_strlen(path) >= 1024 && (bl_err = 1))
		ft_print_error(path, "cd :", "MAX PATH", 0);
	else if (access(path, F_OK) == -1 && (bl_err = 1))
		ft_print_error(path, "cd :", FIL_NS, 0);
	else
	{
		stat(path, &st_stat);
		if (!S_ISDIR(st_stat.st_mode) && (bl_err = 1))
			ft_print_error(FIL_ND, "cd :", path, 0);
		else if (access(path, X_OK) == -1 && (bl_err = 1))
			ft_print_error(FIL_PD, "cd :", path, 0);
	}
	return (bl_err);
}

int cd_options(char **arg, int *flag)
{
    int i;
    int j;

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
                    ft_print_error(CD_OEMSG, "42sh: cd: -", &arg[i][j], 0);
                    return (-1);
                }
            }
        }
        else
            break ;
    }
    return (i);
}

char *get_path(char **arg, char **tmpenv, int flag)
{
	UNUSED(tmpenv);
    if (*(arg + 0) && *(arg + 1))
        return (ft_putstr("42sh: cd: too many arguments\n") ? NULL : NULL);
    else if (*(arg) == NULL && !flag)
        return (ft_get_vrb("HOME",  g_environ));
    else if (*(arg) && *(arg)[0] == '-' && !*(arg + 1))
        return (ft_get_vrb("OLDPWD",  g_environ));
    return (ft_strdup(*arg));
}

/*
**	Builten cd : O
*/

char        *dot_dot_path(char *s, char *pwd)
{
    int cnt;
    char **arr;
    int i;
    int k;

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

char        *correct_path(char *path, t_cdpkg v)
{
    char *ret;
    int  i;

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
    ret = ft_strjoin(getcwd(v.buff, 1024), path + i);
    return (ret);
}

void        cd_symblink(char **pwd, char **oldpwd, t_cdpkg v, char ***env, int *var)
{
    int flag;

    (void)env;
    flag = 0;
    if (v.path[0] == '.' && v.path[1] == '.' && v.path[2] == '/' && (flag = 1))
        v.path = correct_path(v.path, v);
    else if (((ft_strcmp(v.path, ".") == 0 || ft_strcmp(v.path, "./") == 0) ||\
            (ft_strcmp(v.path, *pwd) == 0 && ft_strcmp(v.path, *oldpwd) == 0)) &&\
            *var && (flag = 2))
        v.path = ft_strdup(*pwd);
    else if (!(ft_strcmp(*pwd, v.path) == 0 || ft_strcmp(*oldpwd, v.path) == 0))
        v.path = ft_strjoir(ft_strjoir(getcwd(v.buff, 1024), "/", 0), v.path, 1);
    (flag == 1) ? ft_set_vrb(ft_strjoir("OLDPWD=", ft_get_vrb("PWD",  g_environ), 0), &g_environ, 0) : 0;
    ft_set_vrb(ft_strjoir("PWD=", v.path, 0), &g_environ, 1);
    (!flag) ? ft_set_vrb(ft_strjoir("OLDPWD=", getcwd(v.buff, 1024), 0), &g_environ, 1) : 0;
    (flag == 2) ? ft_set_vrb(ft_strjoir("OLDPWD=", ft_get_vrb("PWD",  g_environ), 0), &g_environ, 0) : 0;
    ft_strdel(pwd);
    ft_strdel(oldpwd);
    *pwd = ft_get_vrb("PWD",  g_environ);
    *oldpwd = ft_get_vrb("OLDPWD",  g_environ);
    chdir(v.path);
    *var = 1;
}

void    cd_ordlink(char **pwd, char **oldpwd, t_cdpkg v, char ***env, int *var)
{
    (void)env;
    if (*var)
        ft_set_vrb(ft_strjoir("OLDPWD=", *pwd, 0),  &g_environ, 1);
    else if (!*var)
        ft_set_vrb(ft_strjoir("OLDPWD=", getcwd(v.buff, 1024), 0),  &g_environ, 1);
    if (ft_strncmp(v.path, "..", 2) == 0 && *var)
        v.path = dot_dot_path(v.path, *pwd);
    chdir(v.path);
    if (*var && !(ft_strcmp(*oldpwd, *pwd) == 0))
        ft_set_vrb(ft_strjoir("PWD=", v.path, 0),  &g_environ, 1);
    else
        ft_set_vrb(ft_strjoir("PWD=", getcwd(v.buff, 1024), 0),  &g_environ, 1);
    *var = 0;
}

int		ft_buil_cd(char **arg, char **env)
{
    t_cdpkg		v;
    static char	*pwd;
    static char	*oldpwd;
    static int	var;

	v.flag = 0;
	if ((v.index = cd_options(arg, &v.flag)) == -1)
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
        cd_symblink(&pwd, &oldpwd, v, &env, &var);
    else
        cd_ordlink(&pwd, &oldpwd, v, &env, &var);
    return (1);
}
