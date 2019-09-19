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
** ft_new_redir : New list redirection ;
*/

t_redir		*ft_new_redir(void)
{
	t_redir	*st_redir;

	st_redir = (t_redir *)malloc(sizeof(t_redir));
	st_redir->next = NULL;
	return (st_redir);
}

/*
** New t_tokens :
*/

t_tokens	*ft_new_token(void)
{
	t_tokens	*st_token;

	st_token = (t_tokens *)malloc(sizeof(t_tokens));
	st_token->token = 0;
	st_token->value = NULL;
	st_token->prev = NULL;
	st_token->next = NULL;
	st_token->indx = -1;
	st_token->is_arg = 0;
	return (st_token);
}
