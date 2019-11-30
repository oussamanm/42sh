/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:56:36 by onouaman          #+#    #+#             */
	/*   Updated: 2019/11/26 15:33:43 by aboukhri         ###   ########.fr       */
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

static int		valid_identifier(char *arg, char *cmd)
{
	int i;

	if (!arg)
		return (0);
	i = -1;
	while (arg[++i])
	{
		if (!ft_isalphanum(arg[i]) || arg[i] == '.' || arg[i] == '/' || arg[0] == '=')
		{
			ft_putstr_fd("42sh: export: `", 2);
			ft_putstr_fd(cmd, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (0);
		}
	}
	return (1);
}

/*
** export Variable
*/

int			built_export(t_tokens *st_tokens)
{
	int i;
	char *temp;

	st_tokens = NEXT;
	if (!st_tokens)
		return (EXIT_SUCCESS);
	temp = NULL;
	i = 1;
	while (st_tokens)
	{
		if (st_tokens->indx == i)
		{
			if (!valid_identifier(st_tokens->value, "export"))
				return (EXIT_FAILURE);
			if (NEXT && NEXT->token == T_EQUAL && NEXT->indx == i)
			{
				temp = ft_strjoir(st_tokens->value, "=", 0);
				if (NEXT->next && NEXT->next->indx == i && T_IS_TXT(NEXT->next->token))
					temp = ft_strjoir(temp, NEXT->next->value, 0);
				ft_set_vrb(temp, &g_environ, 1);
				i++;
			}
			else
			{
				move_to_env(st_tokens->value);
				i++;
			}
		}
		st_tokens = NEXT;
	}
	return (EXIT_SUCCESS);
}

/*
** display intern variables buitin
*/

void			built_set(char **args)
{
	t_intern *lst;

	if (args && *args)
		return ;
	lst = g_intern;
	while (lst)
	{
		ft_putstr(lst->key);
		ft_putchar('=');
		ft_putendl(lst->value);
		lst = lst->next;
	}
}
/*
** Unset Variable
*/

int			built_unset(char **args)
{
	int i;

	if (!args || !*args)
		return (EXIT_SUCCESS);
	i = -1;
	while (args[++i])
	{
		if (!valid_identifier(args[i], "unset"))
			return (EXIT_FAILURE);
		if (!delete_intern_var(args[i], &g_intern))
			ft_unset_vrb(args[i], &g_environ);
	}
	return (EXIT_SUCCESS);
}
