/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:56:36 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/02 11:20:11 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	move_to_env(char *key)
{
	t_intern	*lst;
	char		*vrb;

	lst = g_intern;
	while (lst)
	{
		if (ft_strcmp(key, lst->key) == 0)
		{
			vrb = ft_strjoin(ft_strjoin(lst->key, "="), lst->value);
			ft_set_vrb(vrb, &g_environ, 1);
			exported_vars((t_intern){key, lst->value, NULL}, STDIN_FILENO, 0);
			return ;
		}
		lst = lst->next;
	}
	exported_vars((t_intern){key, NULL, NULL}, STDIN_FILENO, 0);
}

/*
**	Builten env
*/

void	built_env(char **args, char ***tmp_env)
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

void	puterr_identifier(char *arg, char *cmd)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

/*
** display intern variables buitin
*/

void	built_set(t_intern *intern, char **args)
{
	t_intern *lst;

	if ((args && *args) || !intern)
		return ;
	lst = intern;
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

int		built_unset(char **args)
{
	int i;

	if (!args || !*args)
		return (EXIT_SUCCESS);
	i = -1;
	while (args[++i])
	{
		if (!valid_identifier(args[i]))
		{
			puterr_identifier(args[i], "unset");
			return (EXIT_FAILURE);
		}
		delete_intern_var(args[i], &g_intern);
		ft_unset_vrb(args[i], &g_environ);
		exported_vars((t_intern){args[i], NULL, NULL}, STDERR_FILENO, -1);
		if (ft_strcmp("PATH", args[i]) == 0)
			erase_hash_table();
	}
	return (EXIT_SUCCESS);
}
