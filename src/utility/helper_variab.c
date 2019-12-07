/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_variab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:01:46 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 12:01:48 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	ft_get_vrb : return variable (allocated) || NULL :
*/

char		*ft_get_vrb(char *vrb, char **env)
{
	int		len;
	char	*value;

	if (vrb == NULL || env == NULL)
		return (NULL);
	if ((len = ft_strlen(vrb)) == 0)
		return (NULL);
	while (*env != NULL)
	{
		if (ft_strnequ(*env, vrb, len) && (*env)[len] == '=')
		{
			value = ft_strsub(*env, len + 1, ft_strlen(*env) - len - 1);
			return (value);
		}
		env++;
	}
	return (NULL);
}

/*
**  get varaible inside ${}
*/

char		*get_para_expan(char *arg, int *len_vrb)
{
	int		i;
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
	str_rtn = ft_strsub(arg, 1, i - 1);
	*len_vrb += (i + 1);
	return (str_rtn);
}

/*
** check error of bad substitution in expansions
*/

int			helper_error_expans(char *str_cmds, int i)
{
	if (!ft_isalphanum(str_cmds[i]))
	{
		if (!(M_CHECK(str_cmds[i], '?', '$') && (str_cmds[i - 1] == '{' &&
			str_cmds[i + 1] == '}')))
			return (1);
	}
	return (0);
}

/*
** Check if arg entred is variable
*/

int			is_variab_expans(char *cmd)
{
	if (!cmd)
		return (0);
	if (M_CHECK(cmd[0], '$', '?') || ft_isalpha(cmd[0]) ||
		ft_isalnum(cmd[0]) || cmd[0] == '{')
		return (1);
	return (0);
}
