/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vrbs_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhri <aboukhri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 15:59:19 by onouaman          #+#    #+#             */
/*   Updated: 2019/12/08 13:27:23 by aboukhri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	Check if token has T_EQUA in index
*/

int				ft_is_equal(int index, t_tokens *st_tokens)
{
	if (!st_tokens)
		return (0);
	while (st_tokens && st_tokens->indx == index)
	{
		if (st_tokens->token == T_EQUAL && PREV &&
			st_tokens->indx == PREV->indx && PREV->token == T_TXT)
			return (1);
		st_tokens = st_tokens->next;
	}
	return (0);
}

/*
**	Check if last token has cmd
*/

int				ft_check_intern(t_pipes *st_pipe)
{
	t_tokens	*st_tokens;
	int			i;

	st_tokens = st_pipe->st_tokens;
	i = st_tokens->indx - 1;
	while (st_tokens)
	{
		if (st_tokens->indx == i)
			st_tokens = st_tokens->next;
		else
		{
			i++;
			if (!ft_is_equal(i, st_tokens))
				return (0);
		}
	}
	return (1);
}

/*
** Fill inter
*/

void			fill_intern(t_pipes *st_pipe)
{
	t_intern	var;
	t_tokens	*token;
	int			i;
	char		*line;

	if (!st_pipe)
		return ;
	token = st_pipe->st_tokens;
	i = token->indx - 1;
	while (token)
	{
		if (token->indx == i)
			token = token->next;
		else
		{
			i++;
			if (!ft_is_equal(i, token) || !valid_identifier(token->value))
				return ;
			var = get_key_value(token);
			if (ft_strcmp("PATH", var.key) == 0)
				erase_hash_table();
			line = ft_strjoir(ft_strjoin(var.key, "="), var.value, 1);
			add_intern_var(&g_intern, var.key, var.value,
			ft_edit_vrb(line, &g_environ, 1));
			exported_vars(var, STDIN_FILENO, 1);
		}
	}
}

/*
**	Fill temp_environ with g_environ and append new variables
*/

char			**fill_env(char **args)
{
	int		i;
	char	**tmp_env;

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

char			**ft_tokens_arg_env(t_tokens *token)
{
	char		**args;
	t_tokens	*tmp_tokens;
	t_intern	var;
	int			i;
	int			j;

	i = token->indx - 1;
	j = 0;
	tmp_tokens = token;
	while (tmp_tokens->next && (tmp_tokens = tmp_tokens->next))
		;
	args = ft_strr_new(tmp_tokens->indx);
	while (token)
	{
		if (token->indx == i)
			token = token->next;
		else
		{
			if (!ft_is_equal(++i, token) || !valid_identifier(token->value))
				break ;
			var = get_key_value(token);
			args[j++] = ft_strjoir(ft_strjoin(var.key, "="), var.value, 1);
		}
	}
	return (args);
}
