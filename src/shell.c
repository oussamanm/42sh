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
	char		*str_cmds;
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
	while (1337)
	{
		ft_putstr("\033[0;32m42sh $>\033[0m ");
		if ((str_cmds = ft_read_line(his, select, 8)) == NULL)
			continue ;
		// Check incomplete syntax of Sub_shell or Quoting
		compliting_line(&str_cmds, select, his);
		ft_stock_history(his->history, str_cmds, his->his_count);
		his->his_count += (his->his_count < MAX_HISTORY) ? 1 : 0;
		// Execution
		(!(g_pos.exit)) ? ft_multi_cmd(str_cmds, 0) : NULL;
	}
	return (0);
}
