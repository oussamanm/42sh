/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:54:16 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/08 13:18:14 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Split with ; and Check error syntax , and correction args before start
*/

void		ft_multi_cmd(char *str_cmds, int bl_subsh)
{
	char	**args;
	int		i;

	i = 0;
	if (!str_cmds)
		return ;
	str_cmds = ft_strdup(str_cmds);
	args = ft_str_split_q(str_cmds, ";");
	ft_strr_trim(args);
	if (!error_syntax_semi(str_cmds, args) && !error_syntax_expans(str_cmds))
	{
		while (args[i] != NULL)
		{
			args[i] = ft_corr_args(args[i]);
			ft_cmds_setup(args[i], bl_subsh);
			i++;
		}
	}
	ft_strrdel(args);
	ft_strdel(&str_cmds);
}

static void	initial_shell(t_select **select)
{
	g_pos.cmd = NULL;
	g_exit_status = 0;
	call_signal();
	initial_read_line(&g_history, select);
	init_fc_built();
	init_alias_hash();
	setsid();
	g_shellpid = getpid();
	g_proc_sub = 0;
}

int			main(void)
{
	extern char	**environ;
	t_select	*select;

	g_intern = NULL;
	if (ft_set_termcap() == -1)
		ft_err_exit("ERROR in setting Termcap parameters\n");
	set_export_env(environ);
	initial_shell(&select);
	while (1337)
	{
		ft_putstr("\033[0;32m42sh $>\033[0m ");
		if ((ft_read_line(&g_history, select, 8)) == NULL || !g_pos.cmd[0])
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
	}
	return (0);
}
