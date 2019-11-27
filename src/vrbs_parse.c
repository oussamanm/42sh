/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vrbs_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:59:19 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/25 23:53:15 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/// *** Check if token has T_EQUA in index

int				is_tmp_intern(char *arg)
{
	int i;

	i = ft_strchrindex(arg, '=');
	if (i > 0 && arg[i + 1])
		return (1);
	return (0);
}

/// Check if last token has cmd
int				ft_check_tmp(char **args)
{
	int i;

	i = -1;
	while (args && args[++i])
	{
		if (!is_tmp_intern(args[i]))
			return (i + 1);
	}
	return (0);
}


/*
** Fill inter
*/
void			ft_fill_intern(char **args)
{
	int i;
	char **split;

	i = -1;
	while (args && args[++i])
	{
		if (is_tmp_intern(args[i]) && (split = get_key_value(args[i])))
		{
			add_intern_var(split[0], split[1]);
			ft_strrdel(split);
		}
		else
			break ;
	}
}

/*
** Fill temp_environ with g_environ and append new variables
*/

char            **ft_fill_env(char **args, int len)
{
    int     i;
    char    **tmp_env;

    tmp_env = ft_strr_dup(g_environ, ft_strrlen(g_environ) + len + 1);
	i = -1;
    while (args && args[++i])
	{
		if (is_tmp_intern(args[i]))
        	ft_insert_vrb(args[i], &tmp_env, 0);
		else
			break ;
	}
    return (tmp_env);
}
