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

int			ft_init_built(t_pipes *st_pipes, char ***tmp_env)
{
	int i;
	int tmp[3];

	i = -1;
	while (++i < 3)
		tmp[i] = dup(i);
	ft_call_built(st_pipes, tmp_env);
	i = -1;
	while (++i < 3)
		if (dup2(tmp[i], i) == -1 || close(tmp[i]) == -1)
			ft_putendl_fd("Error in dup or close \n", 2);
	// should add return status of builtens
	return (1);
}

/*
**  Call Builtens (close fds of redirection)
*/

int			ft_call_built(t_pipes *st_pipes, char ***tmp_env)
{
	int		rtn;

	rtn = 0;
	if (st_pipes == NULL || st_pipes->args == NULL)
		return (-1);
	if (ft_check_redi(st_pipes) && ft_parse_redir(st_pipes) == PARSE_KO)
		return (REDI_KO);
	if (ft_strcmp((st_pipes->args)[0], "exit") == 0)
		ft_built_exit(st_pipes, tmp_env);
	if (ft_strcmp((st_pipes->args)[0], "env") == 0 && (rtn = 1))
		ft_buil_env(&(st_pipes->args)[1], tmp_env);
	else if (ft_strcmp((st_pipes->args)[0], "export") == 0 && (rtn = 1))
		ft_buil_export(st_pipes->st_tokens);
	else if (ft_strcmp((st_pipes->args)[0], "unset") == 0 && (rtn = 1))
		ft_buil_unset(&(st_pipes->args)[1]);
	else if (ft_strcmp((st_pipes->args)[0], "cd") == 0 && (rtn = 1))
		ft_buil_cd(&(st_pipes->args)[1], *tmp_env);
	else if (ft_strcmp((st_pipes->args)[0], "type") == 0 && (rtn = 1))
		ft_buil_type(&(st_pipes->args)[1], *tmp_env);
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
	else if (!ft_strcmp(arg, "export") || !ft_strcmp(arg, "unset"))
		rtn++;
	else if (!ft_strcmp(arg, "cd") || !ft_strcmp(arg, "type"))
		rtn++;
	return (rtn);
}
