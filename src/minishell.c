/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:54:16 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/15 22:59:16 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Initiale terminle attr , fill struct info and call function Read
*/

void		ft_initial_read_line(t_history *his, t_select **select)
{
	init_history(his);
	//*his = ft_memalloc(sizeof(t_history));
	*select = ft_memalloc(sizeof(t_select));
	(*select)->start = -1;
	(*select)->end = -1;
	(*select)->save = NULL;
	//(*his)->history = ft_alloc_tab();
	//(*his)->his_count = 0;
	ft_save_address(his, select);
}

/*
** Save adresse t_history to t_select , to easy access from other function
*/

void		ft_save_address(t_history **his, t_select **select)
{
	static t_history	*p_his;
	static t_select		*p_select;

	if (*his != NULL && *select != NULL)
	{
		p_his = *his;
		p_select = *select;
	}
	else
	{
		*his = p_his;
		*select = p_select;
	}
}

/*
** Check Error of syntax , call function_exec
*/

void		ft_multi_cmd(char *str_cmds)
{
	char	**args;
	int		i;

	i = 0;
	if ((args = ft_error_syntax(str_cmds)) == NULL)
		return ;
	while (args[i] != NULL)
	{
		/// Correction args by change expansion
		args[i] = ft_corr_args(args[i]);
		ft_cmds_setup(args[i], 0);
		i++;
	}
	ft_strrdel(args);
	ft_strdel(&str_cmds);
}


int			main(void)
{
	extern char	**environ;
	char		*str_cmds;
	t_history	his;
	t_select	*select;

	g_intern = NULL;
	if (ft_set_termcap() == -1)
		ft_err_exit("ERROR in setting Termcap parameters\n");
	ft_initial_read_line(&his, &select);
	ft_call_signal();
	// Duplicate environ vrbs
	g_environ = ft_strr_dup(environ, ft_strrlen(environ));
	//his->path = ft_get_vrb("PATH", g_environ);
	while (1337)
	{
		ft_putstr("\033[0;32m21sh $>\033[0m ");
		//read from history files
		if ((str_cmds = ft_read_line(his, select, 8)) == NULL)
			continue ;
		// Check incomplete syntax of Quoting
		ft_quotes(&str_cmds, select, his);
		// Check incomplete syntax of Sub_shell
		ft_check_subsh(0, &str_cmds, select, his);
		history_readline(&his, 10, str_cmds, &g_pos);//add new command to history
		//ft_stock_history(his->history, str_cmds, his->his_count);
		//his->his_count += (his->his_count < MAX_HISTORY) ? 1 : 0;
		// Execution
		(!(g_pos.exit)) ? ft_multi_cmd(str_cmds) : NULL;
	}
	return (0);
}