/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:50:14 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/01 21:53:41 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/read_line.h"

static int		is_fc_exist(char *cmd)
{
	char	**sp_args;
	char	*fl;
	int		i;

	sp_args = ft_str_split_q(cmd, "\n \t");
	i = 0;
	while (sp_args && sp_args[i] && ft_strchrindex(sp_args[i], '=') > 0)
		i++;
	if (sp_args && sp_args[i] && ft_strcmp(sp_args[i], "fc") == 0)
	{
		read_fc_flags(sp_args + i + 1, &fl, NULL);
		if (ft_strchr(fl, 'e') || ft_strchr(fl, 's') || !ft_strchr(fl, 'l'))
		{
			ft_strrdel(sp_args);
			return (1);
		}
	}
	ft_strrdel(sp_args);
	return (0);
}

/*
**	check if fc builtin exists and in in cmd and has exec flags(e, s)
*/

static int		fc_exec_flag(char *str_cmds)
{
	char	**pv_args;
	int		i;

	if (!str_cmds)
		return (0);
	pv_args = ft_str_split_q(str_cmds, ";");
	i = -1;
	while (pv_args && pv_args[++i])
	{
		if (is_fc_exist(pv_args[i]))
		{
			ft_strrdel(pv_args);
			return (1);
		}
	}
	ft_strrdel(pv_args);
	return (0);
}

int				history_handling(char **str_cmds)
{
	if (ft_strchr(*str_cmds, '!'))
	{
		if (!(*str_cmds = history_expansion(g_history, *str_cmds)))
			return (0);
		ft_putendl(*str_cmds);
	}
	else if (!fc_exec_flag(*str_cmds))
	{
		insert_history(&g_history, *str_cmds);
		history_readline(&g_history, 0, str_cmds);
	}
	return (1);
}
