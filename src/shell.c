/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 05:54:16 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/01 22:58:41 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "read_line.h"

/*
** Initiale terminle attr , fill struct info and call function Read
*/

void		initial_read_line(t_history *his, t_select **select)
{
	restore_history(his);
	g_sign = 0;
	*select = (t_select *)ft_memalloc(sizeof(t_select));
	(*select)->start = -1;
	(*select)->end = -1;
	(*select)->save = NULL;
	save_address(select);
}

/*
** Save adresse t_history to t_select , to easy access from other function
*/

void		save_address(t_select **select)//??
{
	static t_select		*p_select;

	if (*select != NULL)
		p_select = *select;
	else
		*select = p_select;
}

/*
** Initiale alias and hash_table
*/

void		init_alias_hash()
{
	t_aliaspkg *data;
	t_hash **hash_arr;

	data = (t_aliaspkg *)ft_memalloc(sizeof(t_aliaspkg));
	storeaddrstruct(data);
	createaliasfile();
	importaliasfilecontent(NULL);
	hash_arr = (t_hash **)ft_memalloc(sizeof(t_hash *) * SIZE);
	int i = -1;
	
	while (++i < SIZE)
		hash_arr[i] =  NULL;
	store_addr_of_hash(hash_arr, 1);
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

static void	initial_shell(t_select	**select)
{
	g_pos.cmd = NULL;
	g_exit_status = 0;
	call_signal();
	initial_read_line(&g_history, select);
	init_fc_built();
	
	// Initial Alias && HASH
	init_alias_hash();
	
	//start new session for shell
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

	// Duplicate environ vrbs
	g_environ = ft_strr_dup(environ, ft_strrlen(environ));

	// Initail shell (signal, session, read_line, hash_table, alias, fc_built)
	g_fd= open("/dev/ttys001", O_WRONLY);
	initial_shell(&select);
	while (1337)
    {
        ft_putstr("\033[0;32m42sh $>\033[0m ");
        if ((ft_read_line(&g_history, select, 8)) == NULL || !g_pos.cmd[0])
        {
			ft_job_processing();
			continue ;
		}
		convert_neg_to_tab(&g_pos.cmd);
        // Check incomplete syntax of Sub_shell or Quoting
		g_pos.cmd = completing_line(g_pos.cmd, select, &g_history);
        // add command to history	
	  	if (!history_handling(&g_pos.cmd))
			continue ;
		// Execution
		(!g_pos.exit) ? ft_multi_cmd(g_pos.cmd, 0) : NULL;
		ft_job_processing();
		ft_strdel(&g_pos.cmd);
	}
	return (0);
}
