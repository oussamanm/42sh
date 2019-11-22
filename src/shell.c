/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:54:16 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/07 06:09:23 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Initiale terminle attr , fill struct info and call function Read
*/

void		initial_read_line(t_history **his, t_select **select)
{
	*his = ft_memalloc(sizeof(t_history));
	*select = ft_memalloc(sizeof(t_select));
	(*select)->start = -1;
	(*select)->end = -1;
	(*select)->save = NULL;
	(*his)->history = ft_alloc_tab();
	(*his)->his_count = 0;
	save_address(his, select);
}

/*
** Save adresse t_history to t_select , to easy access from other function
*/

void		save_address(t_history **his, t_select **select)
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


void		init_alias_hash()
{
	t_aliaspkg *data;
	t_hash **hash_arr;

	data = (t_aliaspkg *)ft_memalloc(sizeof(t_aliaspkg));
	storeaddrstruct(data);
	createaliasfile();
	importaliasfilecontent();
	hash_arr = (t_hash **)malloc(sizeof(t_hash *) * SIZE);
	int i = -1;
	while (++i < SIZE)
		hash_arr[i] =  NULL;
	store_addr_of_hash(hash_arr, 1);
	// printf("addr of hash_arr %p\n", hash_arr);
}

/*
** handling of history by stock cmd_line in history, and change expansion history
*/

void		handle_history(t_history *his, char *cmd_line)
{
	if (his == NULL || cmd_line == NULL)
		return ;
	ft_stock_history(his->history, g_pos.cmd, his->his_count);
	/// change history with value
	/// call_function_ayoub
	his->his_count += (his->his_count < MAX_HISTORY) ? 1 : 0;
}


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
			/// Correction args by change expansion
			args[i] = ft_corr_args(args[i]);
			ft_cmds_setup(args[i], bl_subsh);
			i++;
		}
	}
	ft_strrdel(args);
	ft_strdel(&str_cmds);
}

int			main(void)
{
	extern char	**environ;
	t_history	*his;
	t_select	*select;

	g_intern = NULL;
	if (ft_set_termcap() == -1)
		ft_err_exit("ERROR in setting Termcap parameters\n");
	initial_read_line(&his, &select);
	call_signal();
	// Duplicate environ vrbs
	g_environ = ft_strr_dup(environ, ft_strrlen(environ));
	his->path = ft_get_vrb("PATH", g_environ);
	// Initial Alias && HASH
	init_alias_hash();
	while (1337)
	{
		ft_putstr("\033[0;32m42sh $>\033[0m ");
		if ((ft_read_line(his, select, 8)) == NULL || !g_pos.cmd[0])
			continue ;
		// Check incomplete syntax of Sub_shell or Quoting
		g_pos.cmd = compliting_line(g_pos.cmd, select, his);
		
		// add command to history
		handle_history(his, g_pos.cmd);

		// Execution
		(!(g_pos.exit)) ? ft_multi_cmd(g_pos.cmd, 0) : NULL;
		ft_job_processing();
		ft_strdel(&g_pos.cmd);
	}
	return (0);
}