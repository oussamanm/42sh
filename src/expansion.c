/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 21:02:13 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/01 21:02:16 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
**  get varaible inside ${}
*/

static char		*get_para_expan(char *arg, int *len_vrb)
{
	int i;
	char	*str_rtn;

	if (!arg)
		return (NULL);
	i = 0;
	str_rtn = NULL;
	while (arg[i])
	{
		if (arg[i] == '}')
			break ;
		i++;
	}
	*len_vrb += (i + 1);
	str_rtn = ft_strsub(arg, 0, i);
	return (str_rtn);
}


/*
**  ft_swap_vrb : Swap Variable with value :
**		in case of - $$ replace with PID
**				   - $(nor alphanum) do nothing
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
	len_vrb = 0;
	j = *index + 1;
	/// get len of variable
	while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_') && ++j && ++len_vrb);

	/// get variable
	if (!len_vrb && arg[j] == '{' && ++len_vrb)
		variable = get_para_expan(&arg[j + 1], &len_vrb);
	else if (!len_vrb && arg[j] != '$' && ++(*index))
		return (arg);
	else
		variable = ft_strsub(arg, *index + 1, len_vrb);

	/// get value
	if (!len_vrb && arg[j] == '$' && ++len_vrb)
		value = ft_itoa((int)getpid());
	else if (!(value = ft_get_vrb(variable, g_environ)) && !(value = get_intern_value(variable))) /// may should add str_dup to rtn of get_intern_value
		value = ft_strnew(0);
	
	/// get result
	result = ft_str_remp(arg, value, *index, len_vrb + 1);
	*index += ft_strlen(value);
	free_addresses((void *[MAX_TAB_ADDR]){&variable, &value, &arg, NULL});
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
		// Conditions ( \ , ", ', $, !, ~ ) respectively
		if (cmd[i] == '\\')
			i += (cmd[i + 1]) ? 1 : 0;
		else if (cmd[i] == '"')
			bl_q = (bl_q == 0) ? 1 : 0;
		else if (cmd[i] == '\'' && !bl_q)
			i += ft_find_char(cmd + i + 1, '\'') + 2;
		/*else if (0 && cmd[i] == '!')
			cmd = expantion_hist(cmd, &i);*/
		else if (cmd[i] == '$' && cmd[i + 1])
			cmd = ft_swap_vrb(cmd, &i);
		else if (cmd[i] == '~' && (i ? (ft_isspace(cmd[i - 1])) : 1) && (cmd[i + 1] == '/' || !cmd[i + 1] || ft_isspace(cmd[i + 1])))
			cmd = ft_str_remp(cmd, ft_get_vrb("HOME", g_environ), i, -1);
		i += cmd[i] != '\0';
	}
	return (cmd);
}


/*
**	ft_remove_quot : Remove Quote from args :
*/

void			ft_remove_quot(char **args)
{
	int		j;
	int		i;
	char	*arg;

	if (args == NULL)
		return ;
	i = -1;
	while (args[++i] != NULL)
	{
		arg = args[i];
		j = -1;
		if ((arg[0] == '\'' || arg[0] == '"') && arg[ft_strlen(arg) - 1] == arg[0])
		{
			ft_strcpy(arg, &arg[1]);
			arg[ft_strlen(arg) - 1] = 0;
		}
	}
}


/*
**	ft_update_tokens : update token by remove quotes
*/

void			ft_update_tokens(t_tokens *st_tokens)
{
	char		*temp;
	t_tokens	*st_temp;

	st_temp = st_tokens;
	while (st_temp)
	{
		if (st_temp->token == T_QUO || st_temp->token == T_DQUO)
		{
			temp = ft_strsub(st_temp->value, 1, ft_strlen(st_temp->value) - 2);
			ft_strdel(&(st_temp->value));
			st_temp->value = temp;
		}
		st_temp = st_temp->next;
	}
}
