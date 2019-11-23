/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vrbs_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:59:19 by onouaman          #+#    #+#             */
/*   Updated: 2019/09/30 15:59:21 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


/// *** Check if token has T_EQUA in index

int				ft_is_equal(int index, t_tokens *st_tokens)
{
	if (!st_tokens)
		return (0);
	while (st_tokens && st_tokens->indx == index)
	{
		if (st_tokens->token == T_EQUAL && PREV && st_tokens->indx == PREV->indx && PREV->token == T_TXT)
			return (1);
		st_tokens = st_tokens->next;
	}
	return (0);
}

/// Check if last token has cmd
int				ft_check_intern(t_pipes *st_pipe)
{
	t_tokens	*st_tokens;
	int			i;

	i = -1;
	st_tokens = st_pipe->st_tokens;
	while (st_tokens)
	{
		if (st_tokens->indx == i)
			st_tokens = st_tokens->next;
		else
		{
			i++;
			if (!ft_is_equal(i, st_tokens))
				return (1);
		}
	}
	//if (st_tokens && M_CHECK(st_tokens->token, T_TXT, T_QUO)) // temp
	//	return (1);
	//else
		return (0); 
}


/*
** Fill inter
*/
void			ft_fill_intern(t_pipes *st_pipe)
{
	t_intern	var;	
	t_tokens	*st_tokens;
	int			i;
	
	if (!st_pipe)
		return ;
	i = -1;
	st_tokens = st_pipe->st_tokens;
	while (st_tokens)
	{
		if (st_tokens->indx == i)
			st_tokens = st_tokens->next;
		else
		{
			i++;
			if (ft_is_equal(i, st_tokens))
			{
				var = get_key_value(st_tokens);
				add_intern_var(var.key, var.value);
			}
			else
				break;
		}
	}
}

/*
** Fill temp_environ with g_environ and append new variables
*/

char            **ft_fill_env(char **args)
{
    int     i;
    char    **tmp_env;

    tmp_env = ft_strr_dup(g_environ, ft_strrlen(g_environ) + ft_strrlen(args));
    i = -1;
    if (!args || !*args)
        return (tmp_env);
    while (args[++i])
        ft_insert_vrb(args[i], &tmp_env, 0);
    return (tmp_env);
}

/*
** Fill temp_variable
*/
char			**ft_tokens_arg_env(t_tokens *st_tokens)
{
	char		**args;
	t_tokens	*tmp_tokens;
	t_intern	var;
	int			i;
	int			j;

	i = -1;
	j = 0;
	tmp_tokens = st_tokens;
	while (tmp_tokens->next && (tmp_tokens = tmp_tokens->next));
	args = ft_strr_new(tmp_tokens->indx);
	while (st_tokens)
	{
		if (st_tokens->indx == i)
			st_tokens = st_tokens->next;
		else
		{
			if (!ft_is_equal(++i, st_tokens))
				break ;
			var = get_key_value(st_tokens);
			args[j++] = ft_strjoir(ft_strjoir(var.key, "=", 0), var.value, 0);
		}
	}
	return (args);
}

