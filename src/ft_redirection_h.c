/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection_h.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onouaman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 17:37:00 by onouaman          #+#    #+#             */
/*   Updated: 2019/08/05 17:37:01 by onouaman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** ft_init_redi : Initiale vrb of rediretion :
*/

void		ft_init_redi(t_redir *st_redir, int type_red)
{
	if (st_redir == NULL)
		return ;
	st_redir->type_red = type_red;
	st_redir->fd_des = -1;
	st_redir->fd_err = -1;
	st_redir->fd_close = -1;
	if (type_red == 1)
		st_redir->fd_red = 1;
	else if (type_red == 0)
		st_redir->fd_red = 0;
	else if (type_red == 2)
		st_redir->fd_red = 1;
	else if (type_red == 3)
		st_redir->fd_red = 0;
	else if (type_red == 4)
		st_redir->fd_red = 0;
	st_redir->fd_file = NULL;
}

/*
** ft_redi_out_h: helper function for ft_redi_out (>& || &>) :
*/

void		ft_redi_out_h(t_redir *st_redir, t_tokens *st_tokens)
{
	if (PREV && PREV->indx == st_tokens->indx &&
		ft_isalldigit(PREV->value) && (PREV->is_arg = 1))
		st_redir->fd_red = ft_atoi(PREV->value);
	if ((st_tokens->value)[1] == '&' && ft_isalldigit(st_tokens->next->value))
		st_redir->fd_des = ft_atoi(st_tokens->next->value);
	else
	{
		st_redir->fd_red = 1;
		st_redir->fd_err = 2;
		st_redir->fd_des = -2;
		st_redir->fd_file = st_tokens->next->value;
	}
	st_tokens->next->is_arg = 1;
}

/*
** ft_apply_hered: Apply redirection her_doc :
*/

void		ft_apply_hered(t_redir *st_redi)
{
	int fds[2];

	if (st_redi == NULL)
		return ;
	if (pipe(fds) == -1)
		ft_putendl_fd("Error in pipe line of here_doc", 2);
	write(fds[1], st_redi->fd_file, ft_strlen(st_redi->fd_file));
	close(fds[1]);
	st_redi->fd_red = 0;
	st_redi->fd_des = fds[0];
}

/*
** ft_error_redir_h: helper funct for ft_error_redir :
*/

int			ft_error_redir_h(t_tokens *st_tokens)
{
	if (st_tokens->token == T_RED_APP_S && NEXT && NEXT->token == T_TXT)
		if (NEXT->indx != st_tokens->indx &&
			NEXT->next && NEXT->next->token < 0)
			return (ft_putendl_fd("syntax error near unexpected token ", 2));
	if (st_tokens->token < T_RED_APP_M)
		return (ft_putendl_fd("syntax error near unexpected token ", 2));
	if (st_tokens->token <= -122 && !ft_strncmp(st_tokens->value, "><", 2))
		return (ft_putendl_fd("syntax error near unexpected token `<'", 2));
	return (0);
}

/*
** ft_error_redir: Check Error syntax of redirection rtn > 0 => error
*/

int			ft_error_redir(t_tokens *st_tokens)
{
	while (st_tokens != NULL)
	{
		if (st_tokens->token == T_RED_OUT_S && NEXT && NEXT->token == T_TXT &&
			NEXT->value && NEXT->value[0] == '&')
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
		if (ft_error_redir_h(st_tokens))
			return (1);
		if (st_tokens->token < 0 &&
			ft_check_char(st_tokens->value, ERRO_IN_AND))
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
		if (st_tokens->token < 0 && (NEXT == NULL || NEXT->token < 0) &&
			st_tokens->token != -145 && st_tokens->token != -143)
			return (ft_putendl_fd("syntax error near unexpected token", 2));
		if (st_tokens->token == T_RED_OUT_A && NEXT &&
			!ft_isalldigit(NEXT->value) && PREV && PREV->indx == st_tokens->indx
			&& ft_isalldigit(PREV->value) && ft_atoi(PREV->value) != 1)
			return (ft_putendl_fd("ambiguous redirect", 2));
		if ((st_tokens->token == T_RED_OUT_A || st_tokens->token == T_RED_HER_D)
			&& NEXT && NEXT->value && NEXT->value[0] == '&')
			return (ft_putendl_fd("syntax error near unexpected token `&'", 2));
		st_tokens = NEXT;
	}
	return (0);
}
