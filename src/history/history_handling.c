/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 17:50:14 by aboukhri          #+#    #+#             */
/*   Updated: 2019/12/08 13:35:12 by aboukhri         ###   ########.fr       */
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

static	void	trim_expansion(char **cmd)
{
	int		i;
	char	*new;

	if (!cmd || !*cmd)
		return ;
	i = -1;
	while (cmd[0][++i])
	{
		if (cmd[0][i] == '!')
			break ;
		else if (ft_isprint(cmd[0][i]) && !ft_isspace(cmd[0][i]))
			return ;
	}
	new = ft_strsub(*cmd, i + 1, ft_strlen(*cmd) - i);
	ft_strdel(cmd);
	*cmd = new;
}

static	int		his_exp_exist(char *str)
{
	int i;
	int q;

	q = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			q = (!q) ? 1 : 0;
		else if (str[i] == '\\' && str[i + 1] == '!')
		{
			i++;
			continue ;
		}
		if (str[i] == '!' && !q)
			return (1);
	}
	return (0);
}

int				history_handling(char **str_cmds)
{
	char	*new;

	if (his_exp_exist(*str_cmds))
	{
		if (!(new = history_expansion(g_history, *str_cmds)))
			return (0);
		if (ft_strcmp(new, *str_cmds) != 0)
		{
			ft_putendl(new);
			ft_strdel(str_cmds);
			*str_cmds = new;
		}
		else
			ft_strdel(&new);
		if (!is_expansion_syntax(*str_cmds))
		{
			insert_history(&g_history, *str_cmds);
			history_readline(&g_history, 0, str_cmds);
			ft_strdel(str_cmds);
			return (0);
		}
	}
	if (!fc_exec_flag(*str_cmds))
		insert_history(&g_history, *str_cmds);
	history_readline(&g_history, 0, str_cmds);
	trim_expansion(str_cmds);
	return (1);
}
