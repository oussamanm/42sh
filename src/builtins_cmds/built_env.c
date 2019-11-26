/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:56:36 by onouaman          #+#    #+#             */
/*   Updated: 2019/11/26 00:53:27 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		move_to_env(char *key)
{
	t_intern    *lst;
	char        *vrb;

	lst = g_intern;
	while (lst)
	{
		if (ft_strcmp(key, lst->key) == 0)
		{
			vrb = ft_strjoin(ft_strjoin(lst->key, "="), lst->value);
			ft_set_vrb(vrb, &g_environ, 1);
		}
		lst = lst->next;
	}
}

/*
**	Builten env
*/

void			built_env(char **args, char ***tmp_env)
{
	int		i;

	i = 0;
	if (tmp_env && *tmp_env)
		ft_put_strr(*tmp_env);
	else
		ft_put_strr(g_environ);
	while (args != NULL && args[i] != NULL)
	{
		if (ft_find_char(args[i], '=') > 0)
			ft_putendl(args[i]);
		else
			break ;
		i++;
	}
}

static int		export_valid_identifier(char *arg)
{
	int i;

	i = -1;
	while (arg[++i])
	{
		if ((!ft_isalphanum(arg[i]) && arg[i] != '=' && arg[i] != '\\') || arg[i] == '.' || arg[i] == '/' || (i == 0 && arg[0] == '='))
		{
			ft_putstr_fd("42sh: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (0);
		}
	}
	return (1);
}

/*
** export Variable
*/

void			built_export(char **args)
{
	int i;

	i = -1;
	while (args && args[++i])
	{
		if (export_valid_identifier(args[i]))
		{
			if (ft_strchr(args[i], '='))
				ft_set_vrb(args[i], &g_environ, 0);
			else
				move_to_env(args[i]);
		}
	}
}

/*
** Unset Variable
*/

void			built_unset(char **args)
{
	int i;

	if (!args || !*args)
		return ;
	i = -1;
	while (args[++i])
	{
		if (!delete_intern_var(args[i], &g_intern))
			ft_unset_vrb(args[i], &g_environ);
	}
}
