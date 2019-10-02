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

static void		move_to_env(char *key)
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

void			ft_buil_env(char **args, char ***tmp_env)
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

/*
** export Variable
*/

void			ft_buil_export(t_tokens *st_tokens)
{
    int i;
    char    *arg;

    i = -1;
    while (st_tokens)
    {
        if (st_tokens->token == T_EQUAL)
        {
            arg = ft_strnew(0);
            if (PREV && PREV->indx == st_tokens->indx)
                arg = ft_strjoir(arg, PREV->value, 1);
            arg = ft_strjoir(arg, st_tokens->value, 1);
            if (NEXT && NEXT->indx == st_tokens->indx)
                arg = ft_strjoir(arg, NEXT->value, 1);
            ft_set_vrb(arg, &g_environ, 1);
        }
        else if (NEXT)
            move_to_env(NEXT->value);
        st_tokens = st_tokens->next;
    }
}

/*
** Unset Variable
*/

void			ft_buil_unset(char **args)
{
    int i;

    if (!args || !*args)
        return ;
    i = -1;
    while (args[++i])
    {
        delete_intern_var(args[i], &g_intern);
        ft_unset_vrb(args[i], &g_environ);
    }
}