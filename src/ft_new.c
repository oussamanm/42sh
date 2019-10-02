/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 05:20:40 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/07 05:20:41 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** New t_cmds
*/

t_cmds		*ft_new_cmds(void)
{
	t_cmds	*st_cmds;

	if ((st_cmds = (t_cmds *)malloc(sizeof(t_cmds))) == NULL)
		return (NULL);
	st_cmds->args = NULL;
	st_cmds->st_jobctr = NULL;
	st_cmds->st_tokens = NULL;
	st_cmds->str_cmd = NULL;
	return (st_cmds);
}

/*
**  New t_jobctr
*/

t_jobctr	*ft_new_jobctr(void)
{
	t_jobctr	*st_jobctr;

	if ((st_jobctr = (t_jobctr *)malloc(sizeof(t_jobctr))) == NULL)
		return (NULL);
	st_jobctr->st_logopr = NULL;
	st_jobctr->st_tokens = NULL;
	st_jobctr->status = 0;
	st_jobctr->next = NULL;
	return (st_jobctr);
}

/*
**  New t_logopr
*/

t_logopr	*ft_new_logopr(void)
{
	t_logopr	*st_logopr;

	if ((st_logopr = (t_logopr *)malloc(sizeof(t_logopr))) == NULL)
		return (NULL);
	st_logopr->st_pipes = NULL;
	st_logopr->st_tokens = NULL;
	st_logopr->status = 0;
	st_logopr->next = NULL;
	return (st_logopr);
}

/*
**	New t_tokens 
*/

t_tokens	*ft_new_token(void)
{
	t_tokens	*st_token;

	if ((st_token = (t_tokens *)malloc(sizeof(t_tokens))) == NULL)
		return (NULL);
	st_token->token = 0;
	st_token->value = NULL;
	st_token->prev = NULL;
	st_token->next = NULL;
	st_token->indx = -1;
	st_token->is_arg = 0;
	return (st_token);
}

/*
**	New t_redir
*/

t_pipes		*ft_new_pipe(void)
{
	t_pipes *st_pipes;

	if ((st_pipes = (t_pipes *)malloc(sizeof(t_pipes))) == NULL)
		return (NULL);
	st_pipes->args = NULL;
	st_pipes->cmd = NULL;
	ft_bzero(st_pipes->fds, 2);
	st_pipes->st_redir = NULL;
	st_pipes->st_tokens = NULL;
	st_pipes->st_intern = NULL;
	st_pipes->tmp_env = NULL;
	st_pipes->next = NULL;
	return (st_pipes);
}

/*
**	New t_redir
*/

t_redir		*ft_new_redir(void)
{
	t_redir	*st_redir;

	if ((st_redir = (t_redir *)malloc(sizeof(t_redir))) == NULL)
		return (NULL);
	st_redir->next = NULL;
	return (st_redir);
}

/*
**	New t_intern
*/

t_intern	*new_intern(char *key, char *value)
{
    t_intern *new;

    if (!(new = (t_intern*)malloc(sizeof(t_intern))))
        return (NULL);
    new->key = (key) ? ft_strdup(key) : NULL;
    new->value = (value) ? ft_strdup(value) : NULL;
    new->next = NULL;
    return (new);
}