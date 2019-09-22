/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:34:51 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/03 04:16:23 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
**	Builten exit : free env , free readline, clear struct t_pipes : O
*/

void		ft_built_exit(t_pipes *st_pipes, char ***env)
{
	UNUSED(st_pipes);
	ft_strrdel(*env);
	ft_clear_readline_struct();
	//ft_clear_cmds(st_pipes);
	exit(0);
}

/*
**	Builten echo : O
*/

void		ft_buil_echo(char **arg)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (arg[++i] != NULL)
	{
		(i != 1) ? ft_putchar(' ') : NULL;
		j = 0;
		while (arg[i][j] != '\0')
			ft_putchar(arg[i][j++]);
	}
	ft_putstr("\n");
	exit(EXIT_SUCCESS);
}

/*
**	Check Error cd builten : O
*/

int			ft_error_cd(char *path, char **arg)
{
	int			bl_err;
	struct stat	st_stat;

	bl_err = 0;
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

/*
**	Builten cd : O
*/

void		ft_buil_cd(char **arg, char ***env)
{
	char	*path;
	char	buff[1024];
	char	*temp;

	if (*arg == NULL)
		path = ft_get_vrb("HOME", *env);
	else
		path = ft_strdup(arg[0]);
	if (*arg != NULL && (*arg)[0] == '-' && (*arg)[1] == '\0')
	{
		ft_strdel(&path);
		path = ft_get_vrb("OLDPWD", *env);
	}
	if (ft_error_cd(path, arg) != 1)
	{
		temp = ft_strjoir("OLDPWD", "=", 0);
		ft_set_vrb(ft_strjoir(temp, getcwd(buff, 1024), 1), env, 1);
		chdir(path);
		temp = ft_strjoir("PWD", "=", 0);
		ft_set_vrb(ft_strjoir(temp, getcwd(buff, 1024), 1), env, 1);
	}
	ft_strdel(&path);
}
