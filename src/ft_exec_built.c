/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 06:25:57 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/07 06:10:18 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** initail builtens : duplicate STD_* , Call builtens , Resete STD_*
*/

void		ft_init_built(t_pipes *st_pipes, char ***env)
{
	int i;
	int tmp[3];

	i = -1;
	while (++i < 3)
		tmp[i] = dup(i);
	ft_call_built(st_pipes, env);
	i = -1;
	while (++i < 3)
		if (dup2(tmp[i], i) == -1 || close(tmp[i]) == -1)
			ft_putendl_fd("Error in dup or close \n", 2);
	return ;
}

/*
**  Call Builtens (close fds of redirection)
*/

int			ft_call_built(t_pipes *st_pipes, char ***env)
{
	int		rtn;

	rtn = 0;
	if (st_pipes == NULL || st_pipes->args == NULL)
		return (-1);
	if (ft_check_redi(st_pipes) && ft_parse_cmd(st_pipes) == PARSE_KO)
		return (REDI_KO);
	if (ft_strcmp((st_pipes->args)[0], "exit") == 0)
		ft_built_exit(st_pipes, env);
	if (ft_strcmp((st_pipes->args)[0], "env") == 0 && (rtn = 1))
		ft_buil_env(&(st_pipes->args)[1], env);
	else if (ft_strcmp((st_pipes->args)[0], "setenv") == 0 && (rtn = 1))
		ft_buil_setenv(&(st_pipes->args)[1], env);
	else if (ft_strcmp((st_pipes->args)[0], "unsetenv") == 0 && (rtn = 1))
		ft_buil_unsetenv(&(st_pipes->args)[1], env);
	else if (ft_strcmp((st_pipes->args)[0], "cd") == 0 && (rtn = 1))
		ft_buil_cd(&(st_pipes->args)[1], env);
	while (st_pipes->st_redir != NULL)
	{
		if (st_pipes->st_redir->fd_des != -1)
			close(st_pipes->st_redir->fd_des);
		st_pipes->st_redir = st_pipes->st_redir->next;
	}
	return (rtn);
}

/*
**	Check if Command builtens
*/

int			ft_check_built(char *arg)
{
	int		rtn;

	rtn = 0;
	if (arg == NULL)
		return (-1);
	if (!ft_strcmp(arg, "exit") || !ft_strcmp(arg, "env"))
		rtn++;
	else if (!ft_strcmp(arg, "setenv") || !ft_strcmp(arg, "unsetenv"))
		rtn++;
	else if (!ft_strcmp(arg, "cd"))
		rtn++;
	return (rtn);
}
