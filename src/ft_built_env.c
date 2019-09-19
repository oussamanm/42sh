/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 06:15:04 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/03 04:24:20 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Builten env : O
*/

void		ft_buil_env(char **args, char ***env)
{
	int		i;

	i = 0;
	if (env != NULL && *env != NULL)
		ft_put_strr(*env);
	while (args != NULL && args[i] != NULL)
	{
		if (ft_find_char(args[i], '=') > 0)
			ft_putendl(args[i]);
		else
			break ;
		i++;
	}
}

/*
**	Builten setenv : O
*/

void		ft_buil_setenv(char **args, char ***env)
{
	if (env == NULL || args == NULL || *args == NULL)
		return ;
	while (*args != NULL)
	{
		if (ft_find_char(*args, '=') > 0)
			ft_set_vrb(*args, env, 0);
		else
			ft_print_error(CMD_NV, "setenv :", *args, 0);
		args++;
	}
	return ;
}

/*
**	Builten unsetenv : unset variable from environ
*/

void		ft_buil_unsetenv(char **args, char ***env)
{
	if (!args || !(*args) || !env || !(*env))
		return ;
	while (*args)
	{
		if (ft_find_char(*args, '=') != -1)
			ft_print_error(CMD_NV, "unsetenv :", *args, 0);
		else
			ft_unset_vrb(*args, env);
		args++;
	}
}
