/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:54:16 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/11 20:13:44 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

void		call_cmds(t_cmds *st_cmds, int bl_subsh)
{
	while (st_cmds)
	{
		ft_cmds_setup(st_cmds, bl_subsh);
		st_cmds = st_cmds->next;
	}
}

/*
** - Lexer - Check Syntax - Parse with ; , handling Alias and Expansion
*/

void		ft_multi_cmd(char *str_cmds, int bl_subsh)
{
	t_tokens	*st_tokens;
	t_cmds		*st_cmds;
	t_cmds		*cmds_head;
	char		**args;

	if (!str_cmds)
		return ;
	cmds_head = NULL;
	args = ft_str_split_q(str_cmds, " \t\n");
	st_tokens = ft_lexer(args);
	handle_alias(&st_tokens);
	if (!error_syntax_semi(str_cmds, args) && !error_syntax_lexer(st_tokens))
	{
		handle_expansions(&st_tokens);
		st_cmds = parse_semicolon(st_tokens);
		cmds_head = st_cmds;
		call_cmds(st_cmds, bl_subsh);
	}
	else
		g_exit_status = 258;
	free_list_cmds(cmds_head);
	free_tokens(st_tokens, (g_exit_status == 258) ? 1 : 0);
	ft_strrdel(args);
}

static void	initial_shell(t_select **select)
{
	g_shellpid = getpid();
	while (1)
	{
		if (g_shellpid == tcgetpgrp(0))
			break ;
		kill(g_shellpid, SIGTTIN);
	}
	g_pos.cmd = NULL;
	g_exit_status = 0;
	call_signal();
	initial_read_line(&g_history, select);
	init_fc_built();
	init_alias_hash();
}

int			main(void)
{
	extern char	**environ;
	t_select	*select;

	set_export_env(environ);
	initial_shell(&select);
	if (ft_set_termcap() == -1)
		ft_err_exit("ERROR in setting Termcap parameters\n");
	while (1337)
	{
		ft_putstr("\033[0;32m42sh $>\033[0m ");
		if ((ft_read_line(&g_history, select, PR_S)) == NULL || !g_pos.cmd[0])
		{
			ft_job_processing();
			continue ;
		}
		g_pos.cmd = completing_line(g_pos.cmd, select, &g_history);
		if (!history_handling(&g_pos.cmd))
			continue ;
		(!g_pos.exit) ? ft_multi_cmd(g_pos.cmd, 0) : NULL;
		ft_job_processing();
		ft_strdel(&g_pos.cmd);
		g_proc_sub = 0;
	}
	return (0);
}
