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

char		**ft_error_multi(char *str_cmds)
{
	char	**args;
	int		i;

	i = 0;
	if (ft_error_separ(str_cmds, ';'))
	{
		ft_putstr_fd("syntax error near unexpected token `;' \n", 2);
		ft_strdel(&str_cmds);
		return (NULL);
	}
	if ((args = ft_str_split_q(str_cmds, ";")) == NULL || *args == NULL)
	{
		ft_putstr_fd("syntax error near unexpected tokenl `;' \n", 2);
		ft_strrdel(args);
		ft_strdel(&str_cmds);
		return (NULL);
	}
	while (args[i])
		if (ft_parse_error(args[i++]))
		{
			ft_strrdel(args);
			ft_strdel(&str_cmds);
			return (NULL);
		}
	return (args);
}

void		ft_multi_cmd(char *str_cmds, char ***environ)
{
	char	**args;
	int		i;

	i = 0;
	if ((args = ft_error_multi(str_cmds)) == NULL)
		return ;
	while (args[i] != NULL)
	{
		args[i] = ft_corr_args(args[i], *environ);
		ft_call_cmdss(args[i], environ);
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
