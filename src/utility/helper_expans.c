/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_expans.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 15:26:33 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/13 15:26:35 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Check error syntax of command ; @
*/

int				error_syntax_semi(char *str_cmds, char **args)
{
	int		temp;
	int		i;

	temp = 0;
	i = -1;
	if (!args || (ft_strrlen(args) > 1 && (!(*args) || (*args)[0] == '\0')))
	{
		print_error(ERR_SEMI, NULL, NULL, 0);
		return (1);
	}
	while (str_cmds[++i])
	{
		if (str_cmds[i] == ';')
		{
			if (temp || str_cmds[0] == ';')
			{
				print_error(ERR_SEMI, NULL, NULL, 0);
				return (1);
			}
			temp = 1;
			continue ;
		}
		temp = (temp && !ft_isspace(str_cmds[i])) ? 0 : temp;
	}
	return (0);
}

/*
**  Function to Change sub_string with string :
*/

char			*ft_str_remp(char *str, char *remp, int start, int len)
{
	char	*rtn;
	int		len_remp;
	int		bl;

	bl = 0;
	if (!str)
		return (NULL);
	if (len < 0)
	{
		len *= -1;
		bl = 1;
	}
	len_remp = ft_strlen(remp);
	rtn = ft_strnew(ft_strlen(str) - len + len_remp);
	ft_strncpy(rtn, str, start);
	ft_strncpy(rtn + start, remp, len_remp);
	ft_strcpy(rtn + start + len_remp, str + start + len);
	if (bl == 1)
	{
		ft_strdel(&str);
		ft_strdel(&remp);
	}
	return (rtn);
}

/*
** helper function for ft_swap_vrb to get variable
*/

static char		*helper_swap_vrb(char *arg, int *len_v, int *j, int index)
{
	char	*variable;

	variable = NULL;
	if (arg[*j] == '{')
	{
		variable = get_para_expan(&arg[*j], len_v);
		if (ft_strlen(variable) == 0)
			ft_strdel(&variable);
	}
	else if ((arg[*j] == '$' || arg[*j] == '?') && ++(*len_v))
		variable = ft_strdup((char[2]){arg[*j], '\0'});
	else
	{
		while (arg[*j] && (ft_isalnum(arg[*j]) || arg[*j] == '_'))
		{
			(*len_v)++;
			(*j)++;
		}
		if (!(*len_v))
			return (ft_strnew(0));
		variable = ft_strsub(arg, index + 1, *len_v);
	}
	return (variable);
}

/*
**  ft_swap_vrb : Swap Variable with value : $$ replace with PID / $? history
*/

static char		*ft_swap_vrb(char *arg, int *index)
{
	char		*variable;
	char		*value;
	char		*result;
	int			len_vrb;
	int			j;

	if (arg == NULL || !(*arg))
		return (NULL);
	value = NULL;
	len_vrb = 0;
	j = *index + 1;
	variable = helper_swap_vrb(arg, &len_vrb, &j, *index);
	if (variable == NULL)
		return (arg);
	else if (M_CHECK(variable[0], '$', '?'))
		value = (variable[0] == '$') ?\
		ft_itoa((int)getpid()) : ft_itoa(g_exit_status);
	else if (!(value = ft_get_vrb(variable, g_environ))
		&& !(value = get_intern_value(variable)))
		value = ft_strnew(0);
	result = ft_str_remp(arg, value, *index, len_vrb + 1);
	*index += (ft_strlen(value) - 1);
	free_addresses((void *[MAX_TAB_ADDR]){&variable, &value, &arg});
	return (result);
}

/*
**  ft_corr_args : Correction cmd_line by change expansions and histr :
*/

char			*ft_corr_args(char *cmd)
{
	int		i;
	int		bl_q;

	i = 0;
	bl_q = 0;
	if (cmd == NULL)
		return (NULL);
	while (cmd[i])
	{
		if (cmd[i] == '\\')
			i += (cmd[i + 1]) ? 1 : 0;
		else if (cmd[i] == '"')
			bl_q = (bl_q == 0) ? 1 : 0;
		else if (cmd[i] == '\'' && !bl_q)
			i += ft_find_char(cmd + i + 1, '\'') + 1;
		else if (cmd[i] == '$' && is_variab_expans(&cmd[i + 1]))
			cmd = ft_swap_vrb(cmd, &i);
		else if (cmd[i] == '~' && (i ? (ft_isspace(cmd[i - 1])) : 1) &&
				(cmd[i + 1] == '/' || !cmd[i + 1] || ft_isspace(cmd[i + 1])))
			cmd = ft_str_remp(cmd, ft_get_vrb("HOME", g_environ), i, -1);
		i += (cmd[i] != '\0');
	}
	return (cmd);
}
