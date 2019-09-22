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

void		ft_initial_read_line(t_history **his, t_select **select)
{
	*his = ft_memalloc(sizeof(t_history));
	*select = ft_memalloc(sizeof(t_select));
	(*select)->start = -1;
	(*select)->end = -1;
	(*select)->save = NULL;
	(*his)->history = ft_alloc_tab();
	(*his)->his_count = 0;
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
** Check Error of syntax , and correction Expansions , call function_exec
*/

void		ft_multi_cmd(char *str_cmds, char ***environ)
{
	char	**args;
	int		i;

	i = 0;
	if ((args = ft_error_syntax(str_cmds)) == NULL)
		return ;
	while (args[i] != NULL)
	{
		ft_cmds_setup(args[i], environ);
		i++;
	}
	ft_strrdel(args);
	ft_strdel(&g_pos.cmd);
}

int			main(void)
{
	extern char	**environ;
	char		*str_cmds;
	t_history	*his;
	t_select	*select;
	
	if (ft_set_termcap() == -1)
		ft_err_exit("ERROR in seting Temcap parameters\n");
	ft_initial_read_line(&his, &select);
	ft_call_signal();
	environ = ft_strr_dup(environ, ft_strrlen(environ));
	his->path = ft_get_vrb("PATH", environ);
	while (1337)
	{
		ft_putstr("\033[0;32m21sh $>\033[0m ");
		if ((str_cmds = ft_read_line(his, select, 8)) != NULL)
		{
			ft_quotes(&str_cmds, select, his);
			ft_stock_history(his->history, str_cmds, his->his_count);
			his->his_count += (his->his_count < MAX_HISTORY) ? 1 : 0;
			if (!(g_pos.exit))
				ft_multi_cmd(str_cmds, &environ);
		}
	}
	ft_strrdel(environ);
	return (0);
}
